QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractchartmodel.cpp \
    barchartmodel.cpp \
    barchartview.cpp \
    controller.cpp \
    filedatah.cpp \
    linechartmodel.cpp \
    linechartview.cpp \
    main.cpp \
    mainwindow.cpp \
    piechartmodel.cpp \
    piechartview.cpp

HEADERS += \
    abstractaxischartmodel.h \
    abstractaxischartview.h \
    abstractchartmodel.h \
    abstractchartview.h \
    barchartmodel.h \
    barchartview.h \
    controller.h \
    filedatah.h \
    linechartmodel.h \
    linechartview.h \
    list.h \
    mainwindow.h \
    piechartmodel.h \
    piechartview.h

#FORMS += \
#    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
