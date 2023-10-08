#include "piechartmodel.h"

pieChartModel::pieChartModel(): numWedges(0){

}

int pieChartModel::getDerivType() const{
    return 2;
}

void pieChartModel::updateCounter(){
    numWedges = data.getLength();
}

int pieChartModel::getCounter() const{
    return numWedges;
}


int pieChartModel::getNumWedges() const{
    return numWedges;
}

double pieChartModel::getWedgeData(int i) const{
    return data.get_element(i)->info;
}

void pieChartModel::removeWedge(int i){
    data.del_element(i);
    updateCounter();
}

void pieChartModel::setWedgeData(double d, int x){
    if(numWedges && x < numWedges){
        data.set_value(d, x);
    } else {
        insertWedge(d , x);
    }
}

void pieChartModel::insertWedge(double d, int x){
    data.insert_element(d,x);
    updateCounter();
}

const List<double>* pieChartModel::getData() const{
    return &data;
}

void pieChartModel::removeData(int x){
    removeWedge(x);
}

void pieChartModel::setData(double d, int x){
    setWedgeData(d, x);
}

void pieChartModel::insertData(double d, int x){
    insertWedge(d, x);
}
