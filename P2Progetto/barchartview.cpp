#include "barchartview.h"
#include <QBarCategoryAxis>
#include <QValueAxis>


barChartView::barChartView(): bar(new QBarSeries()){}

barChartView::~barChartView(){
}

QAbstractAxis *barChartView::getAxi(bool isX) const{
    if(isX){
        return new QBarCategoryAxis;
    }else{
        return new QValueAxis;
    }
}


bool barChartView::hasOnlyVAxis() const{
    return true;
}

void barChartView::createBarSet(const QString &l) const{
    QBarSet* b = new QBarSet("");
    bar->append(b);
    bar->setName(l);
}

void barChartView::clearData(){
    if(bar != nullptr)
        bar->clear();
}

void barChartView::appendData(const qreal &v) {
    bar->barSets().at(0)->append(v);
}

QChart *barChartView::getChartView(const List<double>* data, const QList<QString>* names) {
    QChart * chart = new QChart();
    QBarSet* set = new QBarSet("");
    int length = data->getLength();
    for(int i = 0; i < length; ++i){
        set->append(data->get_element(i)->info);
    }
    bar->append(set);
    QBarCategoryAxis* b = new QBarCategoryAxis;
    length = names->length();
    for(int i = 0; i < length; ++i){
       b->append(names->at(i));
    }
    chart->addSeries(bar);
    chart->addAxis(b, Qt::AlignBottom);
    return chart;
}

abstractChartView *barChartView::getRightType() const{
    return new barChartView();
}

