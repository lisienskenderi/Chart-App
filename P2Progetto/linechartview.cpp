#include "linechartview.h"
#include <QValueAxis>

lineChartView::lineChartView(): line(new QLineSeries()){

}

lineChartView::~lineChartView(){
}

QAbstractAxis *lineChartView::getAxi(bool isX) const{
    QValueAxis* a = new QValueAxis;
    return a;
}


bool lineChartView::hasOnlyVAxis() const{
    return false;
}

void lineChartView::clearData(){
    if(line != nullptr)
        line->clear();
}

void lineChartView::updateChart(double x, double y){
    line->append(x,y);
}

QChart *lineChartView::getChartView(const List<double>* data, const QList<QString>* names) {
    QChart * chart = new QChart();
    clearData();
    int length = data->getLength();
    for(int i = 0; i < length;){
        updateChart(data->get_element(i)->info, data->get_element(i + 1)->info);
        i = i + 2;
    }
    line->setPointLabelsVisible(true);
    line->setPointLabelsColor(Qt::black);
    chart->addSeries(line);
    return chart;
}

abstractChartView *lineChartView::getRightType() const{
    return new lineChartView();
}



