#include "filedatah.h"
#include "piechartmodel.h"
#include "barchartmodel.h"
#include "linechartmodel.h"
#include <iostream>
#include <fstream>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QTextStream>


fileDataH::fileDataH(): hasPath(false){
    chartData.push_back(new lineChartModel());
    chartData.push_back(new barChartModel());
    chartData.push_back(new pieChartModel());
}

abstractChartModel *fileDataH::getRightChart(int chart){
    return chartData.get_element(chart)->info;
}

bool fileDataH::noPath() const{
    return !hasPath;
}


void fileDataH::writeThough() const{
    QJsonObject charts;

    QJsonObject line;
    QJsonArray lineNames;
    QJsonArray xline;
    QJsonArray yline;
    int length = chartData.get_element(0)->info->getCounter();
    for(int i = 0; i < length; ++i){
        QJsonObject data;
        data.insert(QString::number(i), chartData.get_element(0)->info->getElementName(i));
        lineNames.append(data);
    }
    const List<double>* DATA = chartData.get_element(0)->info->getData();
    for(int i = 0; i < length; ++i){
        QJsonObject data;
        data.insert(QString::number(i), DATA->get_element(2*i)->info);
        xline.append(data);
    }
    for(int i = 0; i < length; ++i){
        QJsonObject data;
        data.insert(QString::number(i), DATA->get_element(2*i + 1)->info);
        yline.append(data);
    }
    line["Chart Name"] =  chartData.get_element(0)->info->getName();
    line["Points Names"] = lineNames;
    line["X"] = xline;
    line["Y"] = yline;
    charts["Line Series"] = line;

    QJsonObject bar;
    QJsonArray barNames;
    QJsonArray barValues;
    length = chartData.get_element(1)->info->getCounter();
    DATA = chartData.get_element(1)->info->getData();
    for(int i = 0; i < length; ++i){
        QJsonObject data;
        data.insert(QString::number(i), chartData.get_element(1)->info->getElementName(i));
        barNames.append(data);
    }
    for(int i = 0; i < length; ++i){
        QJsonObject data;
        data.insert(QString::number(i), DATA->get_element(i)->info);
        barValues.append(data);
    }
    bar["Chart Name"] =  chartData.get_element(1)->info->getName();
    bar["Column Names"] = barNames;
    bar["Values"] = barValues;
    charts["Bar Series"] = bar;

    QJsonObject pie;
    QJsonArray pieNames;
    QJsonArray pieValues;
    length = chartData.get_element(2)->info->getCounter();
    DATA = chartData.get_element(2)->info->getData();
    for(int i = 0; i < length; ++i){
        QJsonObject data;
        data.insert(QString::number(i), chartData.get_element(2)->info->getElementName(i));
        pieNames.append(data);
    }
    for(int i = 0; i < length; ++i){
        QJsonObject data;
        data.insert(QString::number(i), DATA->get_element(i)->info);
        pieValues.append(data);
    }
    pie["Chart Name"] =  chartData.get_element(2)->info->getName();
    pie["Slices Names"] = pieNames;
    pie["Values"] = pieValues;
    charts["Pie Series"] = pie;

    QJsonDocument fileJ;
    fileJ.setObject(charts);
    QByteArray rawData = fileJ.toJson();
    QFile doc(path);
    if( doc.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) ){
        QTextStream iStream( &doc );
        iStream << rawData;
        doc.close();
    } else {
        std::cout << "file open failed: " << path.toStdString() << std::endl;
    }
}

void fileDataH::loadUpModel(){
    QFile doc(path);
    if( doc.open( QIODevice::ReadOnly ) ){
        QByteArray bytes = doc.readAll();
        doc.close();

        QJsonParseError jsonError;
        QJsonDocument charts = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError ){
            std::cout << "fromJson failed: " << jsonError.errorString().toStdString() << std::endl;
            return ;
        }
        if( charts.isObject() ){
            QJsonObject chart = charts.object();
            abstractChartModel* chartPointer;
            for(int i = 0; i < 3; ++i){
                chartPointer = chartData.get_element(i)->info;
                delete chartPointer;
                chartData.get_element(i)->info = nullptr;
            }
            delete chartData.pop_back()->info;
            delete chartData.pop_back()->info;
            delete chartData.pop_back()->info;
            chartData.push_back(new lineChartModel());
            chartData.push_back(new barChartModel());
            chartData.push_back(new pieChartModel());

            QJsonObject lineName = chart["Line Series"].toObject();
            QJsonArray lineX = chart["Line Series"].toObject()["X"].toArray();
            QJsonArray lineY = chart["Line Series"].toObject()["Y"].toArray();
            QJsonArray lineNames = chart["Line Series"].toObject()["Points Names"].toArray();
            chartPointer = chartData.get_element(0)->info;
            int length = lineX.size();
            for(int i = 0; i < length; ++i){
                chartPointer->insertData(0, i* 2);
            }
            for(int i = 0; i < length; ++i){
                chartPointer->setData(lineX.at(i).toObject().value(QString::number(i)).toDouble(), 2*i);
                chartPointer->setData(lineY.at(i).toObject().value(QString::number(i)).toDouble(), 2*i + 1);
            }
            for(int i = 0; i < length; ++i){
                chartPointer->addElementName(lineNames.at(i).toObject().value(QString::number(i)).toString(), i);
            }
            chartPointer->setName(lineName["Chart Name"].toString());

            chartPointer = chartData.get_element(1)->info;
            QJsonObject barName = chart["Bar Series"].toObject();
            QJsonArray barNames = chart["Bar Series"].toObject()["Column Names"].toArray();
            QJsonArray barValues = chart["Bar Series"].toObject()["Values"].toArray();
            length = barNames.size();
            for(int i = 0; i < length; ++i){
                chartPointer->insertData(barValues.at(i).toObject().value(QString::number(i)).toDouble(), i);
            }
            for(int i = 0; i < length; ++i){
                chartPointer->addElementName(barNames.at(i).toObject().value(QString::number(i)).toString(), i);
            }
            chartPointer->setName(barName["Chart Name"].toString());

            chartPointer = chartData.get_element(2)->info;
            QJsonObject pieName = chart["Pie Series"].toObject();
            QJsonArray pieNames = chart["Pie Series"].toObject()["Slices Names"].toArray();
            QJsonArray pieValues = chart["Pie Series"].toObject()["Values"].toArray();
            length = pieNames.size();
            for(int i = 0; i < length; ++i){
                chartPointer->insertData(pieValues.at(i).toObject().value(QString::number(i)).toDouble(), i);
            }
            for(int i = 0; i < length; ++i){
                chartPointer->addElementName(pieNames.at(i).toObject().value(QString::number(i)).toString(), i);
            }
            chartPointer->setName(pieName["Chart Name"].toString());
        }
    }
}

void fileDataH::changePath(const QString& p){
    path = p;
    hasPath = true;
}
