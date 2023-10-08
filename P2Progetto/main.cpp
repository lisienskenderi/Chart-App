#include "mainwindow.h"

#include <QApplication>
#include <QLineSeries>
#include <QPointF>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    controller c;
    c.setView(&w);
    w.init(&c);
    w.setMinimumSize(QGuiApplication::primaryScreen()->availableGeometry().size() * 0.6);


    w.connectMenu();
    w.show();
    c.updateGraphPlot();
    return a.exec();
}
