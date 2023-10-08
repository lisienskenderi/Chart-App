#include "linechartmodel.h"


lineChartModel::lineChartModel(): numPoints(0){
    xAxiRange.push_back(0);
    yAxiRange.push_back(0);
    xAxiRange.push_back(0);
    yAxiRange.push_back(0);
}

lineChartModel::~lineChartModel(){
    abstractChartModel::~abstractChartModel();
}

int lineChartModel::getDerivType() const{
    return 0;
}

void lineChartModel::updateCounter(){
    numPoints = (data.getLength())/2;
}

int lineChartModel::getCounter() const{
    return numPoints;
}

double lineChartModel::getMaxData(int i) const{
    double max = 0;
    for(int j = 0; j < numPoints && data.getLength(); ++j){
        if(max < data.get_element(2*j + 2 - i)->info){
            max = data.get_element(2*j + 2 - i)->info;
        }
    }
    return max;
}

double lineChartModel::getMinData(int i) const{
    double min = 0;
    for(int j = 0; j < numPoints && data.getLength(); ++j){
        if(min > data.get_element(2*j + 2 - i)->info){
            min = data.get_element(2*j + 2 - i)->info;
        }
    }
    return min;
}

List<double> *lineChartModel::getMaxAxi() const{
    List<double>* aux = new List<double>();
    aux->push_back(xAxiRange.get_element(1)->info);
    aux->push_back(yAxiRange.get_element(1)->info);
    return aux;
}

List<double> *lineChartModel::getMinAxi() const{
    List<double>* aux = new List<double>();
    aux->push_back(xAxiRange.get_element(0)->info);
    aux->push_back(yAxiRange.get_element(0)->info);
    return aux;
}

double lineChartModel::getPointData(int x) const{
    return data.get_element(x)->info;
}

void lineChartModel::removePointData(int x){
    data.del_element(x);
    data.del_element(x);
    updateCounter();
    xAxiRange.set_value(getMinData(1), 0);
    xAxiRange.set_value(getMaxData(1), 1);
    yAxiRange.set_value(getMinData(2), 0);
    yAxiRange.set_value(getMaxData(2), 1);
}

void lineChartModel::setPointData(double d,int x){
    if(numPoints && x <= 2 * numPoints){
        data.set_value(d, x);
        if(x%2){
            if(yAxiRange.get_element(0)->info > d){
                yAxiRange.set_value(d, 0);
            }
            if(yAxiRange.get_element(0)->info < d){
                yAxiRange.set_value(d, 1);
            }
        }else{
            if(xAxiRange.get_element(0)->info > d){
                xAxiRange.set_value(d, 0);
            }
            if(xAxiRange.get_element(0)->info < d){
                xAxiRange.set_value(d, 1);
            }
        }
    } else {
        insertPoint(d, x);
    }
}

void lineChartModel::insertPoint(double d, int x){
    data.insert_element(d, x);
    data.insert_element(d, x);
    if(x%2){
        if(yAxiRange.get_element(0)->info > d){
            yAxiRange.set_value(d, 0);
        }
        if(yAxiRange.get_element(0)->info < d){
            yAxiRange.set_value(d, 1);
        }
    }else{
        if(xAxiRange.get_element(0)->info > d){
            xAxiRange.set_value(d, 0);
        }
        if(xAxiRange.get_element(0)->info < d){
            xAxiRange.set_value(d, 1);
        }
    }
    updateCounter();
}


const List<double>* lineChartModel::getData() const{
    return &data;
}

void lineChartModel::removeData(int x){
    removePointData(x);
}

void lineChartModel::setData(double d, int x){
    setPointData(d,x);
}

void lineChartModel::insertData(double d, int x){
    insertPoint(d, x);
}
