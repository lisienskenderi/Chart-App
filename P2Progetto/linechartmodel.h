#ifndef LINECHARTMODEL_H
#define LINECHARTMODEL_H

#include "abstractaxischartmodel.h"

class lineChartModel : public abstractAxisChartModel{
private:
    int numPoints;
    List<double> data;
    List<double> xAxiRange;
    List<double> yAxiRange;
public:
    lineChartModel();
    ~lineChartModel() override;

    int getDerivType() const override;

    virtual void updateCounter() override;
    virtual int getCounter() const override;

    double getMaxData(int i) const;
    double getMinData(int i) const;
    List<double>* getMaxAxi() const override;
    List<double>* getMinAxi() const override;

    double getPointData(int x = 0) const;
    void removePointData(int x = 0);
    void setPointData(double d, int x = 0);
    void insertPoint(double d,int x = 0);

    const List<double>* getData() const override;
    void removeData(int x =0) override;
    void setData(double d, int x = 0) override;
    void insertData(double d, int x = 0) override;
};

#endif // LINECHARTMODEL_H
