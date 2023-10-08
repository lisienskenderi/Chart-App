#include "controller.h"
#include <QChart>
#include "abstractaxischartmodel.h"
#include "linechartview.h"
#include "piechartview.h"
#include "barchartview.h"
#include "abstractchartview.h"
#include <QValueAxis>

controller::controller(QObject* p): QObject(p){
    model = chartDataH.getRightChart(0);
}


void controller::setView(MainWindow *v){
    view = v;
    chartView = nullptr;
}

void controller::getLineChartView(){
    chartView = new lineChartView;
}

void controller::getBarChartView(){
    chartView = new barChartView;
}

void controller::getPieChartView(){
    chartView = new pieChartView;
}

void controller::getLineChartModel(){
    model = chartDataH.getRightChart(0);
}

void controller::getBarChartModel(){
    model = chartDataH.getRightChart(1);
}

void controller::getPieChartModel(){
    model = chartDataH.getRightChart(2);
}

int controller::getElemNumber(){
    return model->getCounter();
}

void controller::initGrid(){
    QStringList s;
    unsigned int i = model->getCounter();
    const List<double> * data = model->getData();
    if(model->getDerivType() == 0){
        view->setGridColumn(3);
        for(unsigned int j = 0; j < i; ++j){
            view->addEleGrid();
            view->setCellName((model->getElementName(j)), j, 0);
        }
        s << "Point Name" << "X" << "Y";
        view->setGridHeaders(&s);
        i = data->getLength()/2;
        for(unsigned int j = 0; j < i; ++j){
            view->setCellData(data->get_element((2*j))->info, j, 1);
            view->setCellData(data->get_element(2*j + 1)->info, j, 2);
        }
    } else {
        view->setGridColumn(2);
        for(unsigned int j = 0; j < i; ++j){
            view->addEleGrid();
            view->setCellName((model->getElementName(j)), j, 0);
        }
        s << "Element Name" << "Value";
        view->setGridHeaders(&s);
        i = data->getLength();
        for(unsigned int j = 0; j < i; ++j){
            view->setCellData(data->get_element(j)->info,j,1);
        }
    }
    if(model->getName().isEmpty()){
        view->setChartName("Default");
    }else{
        view->setChartName((model->getName()));
    }
}

void controller::setUpChart(){
    chartView = new lineChartView;

}

void controller::updateModel(int x, int y){
    const List<double>* d = model->getData();
    if(d->getLength() != 0 && !view->changed()){
    if(y == 0){
        QString s = view->getCellName(x);
        model->setElementName(s, x);
    } else {
        const QString& tmp = view->getCellInput(x,y);
        if(tmp != "0" && !view->getCellInput(x,y).toDouble()) {
            view->hasChanged(true);
            if(view->getGridColumn() == 3){
                view->setCellData(d->get_element((2*x) + y - 1)->info, x, y);
            }else{
                view->setCellData(d->get_element(x)->info, x, y);
            }
            view->errorDialog();
        } else {
            double d = view->getCellData(x, y);
            if(view->getGridColumn() == 3){
                model->setData(d, (2*x) + y - 1);
            }else{
                model->setData(d, x);
            }
        }
    }}else{
        view->hasChanged(false);
    }
}

void controller::lineVM(){
    view->cleanGrid();
    getLineChartModel();
    initGrid();
    if(chartView)
        delete chartView;
    getLineChartView();
    updateGraphPlot();
}

void controller::barVM(){
    view->cleanGrid();
    getBarChartModel();
    initGrid();
    if(chartView)
        delete chartView;
    getBarChartView();
    updateGraphPlot();
}

void controller::pieVM(){
    view->cleanGrid();
    getPieChartModel();
    initGrid();
    if(chartView)
        delete chartView;
    getPieChartView();
    updateGraphPlot();
}

void controller::addCell(){
    model->insertData(0, (view->getCellNum() - 1) * 2);
    model->addElementName("Default", view->getCellNum() - 1);

    view->insertEleGrid(view->getCellNum());
}

void controller::remCell(){
    view->removeEleGrid(view->getCellRemNum() - 1);
    model->removeData((view->getCellRemNum() - 1) * 2);
    model->removeElementName(view->getCellRemNum() - 1);
}

void controller::updateGraphPlot(){
    QChart * chart;
    chartView = chartView->getRightType();
    if(model->getDerivType() != 0){
        QList<QString> names;
        for(int i = 0; i < model->getCounter(); ++i){
           names.append((model->getElementName(i)));
        }
        chart = chartView->getChartView(model->getData(), &names);
    }else{
        chart = chartView->getChartView(model->getData());
        chart->legend()->hide();
    }
    if(model->getDerivType() == 1){
        QValueAxis* y = new QValueAxis;
        y->setMin(static_cast<abstractAxisChartModel*>(model)->getMinAxi()->get_element(0)->info);
        y->setMax(static_cast<abstractAxisChartModel*>(model)->getMaxAxi()->get_element(0)->info);
        chart->addAxis(y, Qt::AlignLeft);
        chart->legend()->hide();
    }else{
        chart->createDefaultAxes();
    }
    chart->setTitle(model->getName());
    view->updateChart(chart);
}

void controller::setName(){
    model->setName((view->getNameEnter()));
    view->setChartName((model->getName()));
}

void controller::setPath(const QString &path){
    chartDataH.changePath(path);
    getDataFromJson();
}

void controller::setPathNew(const QString& path){
    QString path1 = path;
    chartDataH.changePath(path1.append(".json"));
}

void controller::checkPath(){
    if(chartDataH.noPath()){
        view->saveAs();
    }else{
        createJsonFile();
    }
}

void controller::createJsonFile(){
    chartDataH.writeThough();
}

void controller::getDataFromJson(){
    chartDataH.loadUpModel();
    lineVM();
}
