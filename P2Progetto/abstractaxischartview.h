#ifndef ABSTRACTAXISCHARTVIEW_H
#define ABSTRACTAXISCHARTVIEW_H

#include "abstractchartview.h"
#include <QAbstractAxis>

class abstractAxisChartView : public abstractChartView
{
public:
    abstractAxisChartView() = default;
    virtual QAbstractAxis *getAxi(bool isX) const = 0;
    virtual bool hasOnlyVAxis() const = 0;
};

#endif // ABSTRACTAXISCHARTVIEW_H
