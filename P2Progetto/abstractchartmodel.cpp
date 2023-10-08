#include "abstractchartmodel.h"




abstractChartModel::~abstractChartModel(){
}

void abstractChartModel::setName(const QString& n){
    chartName = n;
}

const QString& abstractChartModel::getName() const{
    return chartName;
}

QString abstractChartModel::getElementName(int i) const{
    if(elementName.get_element(i)){
        return elementName.get_element(i)->info;
    }
    return "Default";
}

void abstractChartModel::removeElementName(int i){
    elementName.del_element(i);
}

void abstractChartModel::setElementName(QString name, int x){
    if(elementName.getLength() <= x){
        addElementName(name, x);
    } else {
        elementName.set_value(name, x);
    }
}

void abstractChartModel::addElementName(QString name, int x){
    elementName.insert_element(name, x);
}
