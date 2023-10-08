#include "barchartmodel.h"


barChartModel::barChartModel(): numCol(0){
    axiRange.push_back(0);
    axiRange.push_back(0);
}

int barChartModel::getDerivType() const{
    return 1;
}

void barChartModel::updateCounter(){
    numCol = data.getLength();
}

int barChartModel::getCounter() const{
    return numCol;
}

double barChartModel::getMaxData() const{
    double max = 0;
    for(int i = 0; i < numCol && data.getLength(); ++i){
        if(max < data.get_element(i)->info){
            max = data.get_element(i)->info;
        }
    }
    return max;
}

double barChartModel::getMinData() const{
    double min = 0;
    for(int i = 0; i < numCol && data.getLength(); ++i){
        if(min > data.get_element(i)->info){
            min = data.get_element(i)->info;
        }
    }
    return min;
}

List<double> *barChartModel::getMaxAxi() const{
    List<double>* aux = new List<double>();
    aux->push_back(axiRange.get_element(1)->info);
    return aux;
}

List<double> *barChartModel::getMinAxi() const{
    List<double>* aux = new List<double>();
    aux->push_back(axiRange.get_element(0)->info);
    return aux;
}

double barChartModel::getCellData(int x) const{
    return data.get_element(x)->info;
}

void barChartModel::removeCellData(int x){
    data.del_element(x);
    updateCounter();
    axiRange.set_value(getMinData(), 0);
    axiRange.set_value(getMaxData(), 1);
}

void barChartModel::setCellData(double d,int x){
    if(numCol && x < numCol){
        data.set_value(d,x);
        if(axiRange.get_element(0)->info > d){
            axiRange.set_value(d, 0);
        }
        if(axiRange.get_element(1)->info < d){
            axiRange.set_value(d, 1);
        }
    } else{
        insertCell(d, x);
    }
}

void barChartModel::insertCell(double d, int x){
    data.insert_element(d,x);
    if(axiRange.get_element(0)->info > d){
        axiRange.set_value(d, 0);
    }
    if(axiRange.get_element(1)->info < d){
        axiRange.set_value(d, 1);
    }
    updateCounter();
}



const List<double>* barChartModel::getData() const{
    return &data;
}

void barChartModel::removeData(int x){
    removeCellData(x);
}

void barChartModel::setData(double d, int x){
    setCellData(d,x);
}

void barChartModel::insertData(double d, int x){
    insertCell(d, x);
}
