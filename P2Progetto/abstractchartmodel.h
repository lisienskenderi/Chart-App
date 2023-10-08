#ifndef ABSTRACTCHARTMODEL_H
#define ABSTRACTCHARTMODEL_H

#include <QString>
#include "list.h"

class abstractChartModel {
private:
    QString chartName;
    List<QString> elementName ;
public:
    abstractChartModel() = default;
    virtual ~abstractChartModel();

    virtual int getDerivType() const = 0;

    virtual void updateCounter() = 0;
    virtual int getCounter() const = 0;

    void setName(const QString& n);
    const QString& getName() const;

    QString getElementName(int i) const;
    void removeElementName(int i);
    void setElementName(QString name, int x);
    void addElementName(QString name, int x);

    virtual const List<double>* getData() const = 0;
    virtual void removeData(int x =0) = 0;
    virtual void setData(double d, int x = 0) = 0;
    virtual void insertData(double d, int x = 0) = 0;
};

#endif // ABSTRACTCHARTMODEL_H
