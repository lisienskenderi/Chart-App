#ifndef FILEDATAH_H
#define FILEDATAH_H
#include "abstractchartmodel.h"
#include <QJsonDocument>

class fileDataH{
private:
    List<abstractChartModel*> chartData;
    QString path;
    bool hasPath;
public:
    fileDataH();


    abstractChartModel *getRightChart(int chart);
    bool noPath() const;

    void writeThough() const;
    void loadUpModel();
    void changePath(const QString& p);
};

#endif // FILEDATAH_H
