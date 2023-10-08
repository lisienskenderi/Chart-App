#ifndef ABSTRACTAXISCHARTMODEL_H
#define ABSTRACTAXISCHARTMODEL_H

#include "abstractchartmodel.h"

class abstractAxisChartModel : public abstractChartModel{
public:
    abstractAxisChartModel() = default;

    virtual List<double>* getMaxAxi() const = 0;
    virtual List<double>* getMinAxi() const = 0;

};

#endif // ABSTRACTAXISCHARTMODEL_H
