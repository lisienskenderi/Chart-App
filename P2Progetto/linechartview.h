#ifndef LINECHARTVIEW_H
#define LINECHARTVIEW_H

#include <QLineSeries>
#include <QPointF>
#include "abstractaxischartview.h"


class lineChartView : public abstractAxisChartView{
private:
    QLineSeries* line;
public:
    lineChartView();
    ~lineChartView() override;

    QAbstractAxis *getAxi(bool isX) const override;
    bool hasOnlyVAxis() const override;
    void clearData() override;
    void updateChart(double x , double y);
    QChart *getChartView(const List<double>* data, const QList<QString>* names = nullptr) override;
    abstractChartView *getRightType() const override;
};

#endif // LINECHARTVIEW_H
