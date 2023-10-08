#include "piechartview.h"


pieChartView::pieChartView(): pie(new QPieSeries()){}

pieChartView::~pieChartView(){
}


void pieChartView::clearData(){
    if(pie != nullptr)
        pie->clear();
}

void pieChartView::appendSlice(QString l, qreal v) {
    pie->append(new QPieSlice(l, v));
}


QChart *pieChartView::getChartView(const List<double>* data, const QList<QString>* names) {
    QChart * chart = new QChart();
    int length = data->getLength();
    for(int i = 0; i < length; ++i){
        appendSlice(names->at(i),data->get_element(i)->info);
    }
    chart->addSeries(pie);
    return chart;
}

abstractChartView *pieChartView::getRightType() const{
    return new pieChartView();
}
