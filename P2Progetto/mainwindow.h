#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QWidget>
#include <QMainWindow>
#include <iostream>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QDialog>
#include <QSpinBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include "abstractchartview.h"
class controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectMenu();

    void init(controller *c);
    void setGridColumn(int i);
    int getGridColumn() const;
    void addEleGrid();
    void insertEleGrid(int x);
    void removeEleGrid(int x);
    void setGridHeaders(QStringList* s);
    void setCellData(qreal v, int x, int y);
    void setCellName(QString s, int x, int y);
    QString getCellInput(int x, int y) const;
    qreal getCellData(int x, int y) const;
    QString getCellName(int x) const;

    void updateChart(QChart* v);

    void setChartName(const QString& s);
    int getCellNum();
    int getCellRemNum();
    QString getNameEnter();

    void cleanGrid();
    void setHeaderGrid(int row, QString s);

    bool changed() const;
    void hasChanged(bool b);

private:
    void menuIn(QMenuBar* layout);
    void buttonIn(QHBoxLayout* layout);
    void contentIn(QHBoxLayout* layout);
    void connectButtons();

    controller* cont;
    abstractChartView* chartView;
    QChartView* chartPlot;
    QTableWidget* grid;
    QPushButton* lineGraph;
    QPushButton* barGraph;
    QPushButton* pieGraph;
    QPushButton* updateGraph;
    QPushButton* addCell;
    QPushButton* removeCell;
    QMenu* file;
    QMenu* chart;
    QMenu* edit;
    QSpinBox* numberAdd;
    QSpinBox* numberRem;
    QLabel* chartName;
    QLineEdit* enterName;
    bool changedGrid;
public slots:
    void errorDialog();
    void saveAs();

private slots:
    void addCellDialog();
    void removeCellDialog();
    void setNameDialog();
    void openFile();
};
#endif // MAINWINDOW_H
