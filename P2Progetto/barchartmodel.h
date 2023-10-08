#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include "abstractaxischartmodel.h"

class barChartModel : public abstractAxisChartModel{
private:
    int numCol;
    List<double> data;
    List<double> axiRange;
public:
    barChartModel();
    ~barChartModel() override = default;

    int getDerivType() const override;

    virtual void updateCounter() override;
    virtual int getCounter() const override;

    double getMaxData() const;
    double getMinData() const;
    List<double>* getMaxAxi() const override;
    List<double>* getMinAxi() const override;

    double getCellData(int x = 0) const;
    void removeCellData(int x = 0);
    void setCellData(double d, int x = 0);
    void insertCell(double d, int x = 0);

    const List<double>* getData() const override;
    void removeData(int x =0) override;
    void setData(double d, int x = 0) override;
    void insertData(double d, int x = 0) override;
};

#endif // BARCHARTMODEL_H
