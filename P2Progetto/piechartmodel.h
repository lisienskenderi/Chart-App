#ifndef PIECHARTMODEL_H
#define PIECHARTMODEL_H

#include "abstractchartmodel.h"

class pieChartModel : public abstractChartModel{
private:
    int numWedges;
    List<double> data;
public:
    pieChartModel();
    ~pieChartModel() override = default;

    int getDerivType() const override;

    virtual void updateCounter() override;
    virtual int getCounter() const override;

    int getNumWedges() const;

    double getWedgeData(int i) const;
    void removeWedge(int i);
    void setWedgeData(double d, int x);
    void insertWedge(double d, int x);

    const List<double>* getData() const override;
    void removeData(int x =0) override;
    void setData(double d, int x = 0) override;
    void insertData(double d, int x = 0) override;
};

#endif // PIECHARTMODEL_H
