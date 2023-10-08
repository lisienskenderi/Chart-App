#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTableWidget>
#include "abstractchartmodel.h"
#include "abstractchartview.h"
#include "mainwindow.h"
#include "filedatah.h"



class controller: public QObject{
    Q_OBJECT
private:
    fileDataH chartDataH;
    abstractChartModel* model;
    MainWindow* view;
    abstractChartView* chartView;
public:
    controller(QObject* p = nullptr);
    void setView(MainWindow* v);

    void getLineChartView();
    void getBarChartView();
    void getPieChartView();

    void getLineChartModel();
    void getBarChartModel();
    void getPieChartModel();

    int getElemNumber();
    void initGrid();
    void setUpChart();

public slots:
    void updateModel(int x, int y);
    void lineVM();
    void barVM();
    void pieVM();
    void addCell();
    void remCell();
    void updateGraphPlot();
    void setName();
    void setPath(const QString& path);
    void setPathNew(const QString& path);
    void checkPath();
    void createJsonFile();
    void getDataFromJson();
};

#endif // CONTROLLER_H
