#ifndef ABSTRACTCHARTVIEW_H
#define ABSTRACTCHARTVIEW_H

#include "list.h"
#include <QChart>
#include <QChartView>


class abstractChartView{
public:
    abstractChartView() = default;
    virtual ~abstractChartView() = default;
    virtual void clearData() = 0;
    virtual abstractChartView* getRightType() const = 0;
    virtual QChart* getChartView(const List<double>* data, const QList<QString>* names = nullptr) = 0;
};

#endif // ABSTRACTCHARTVIEW_H
