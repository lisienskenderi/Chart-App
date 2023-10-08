#ifndef PIECHARTVIEW_H
#define PIECHARTVIEW_H

#include <QPieSeries>
#include <QPieSlice>
#include <QString>
#include <QList>
#include "abstractchartview.h"

class pieChartView : public abstractChartView{
private:
    QPieSeries* pie;
public:
    pieChartView();
    ~pieChartView() override;

    void clearData() override;
    void appendSlice(QString l, qreal v);
    QChart* getChartView(const List<double>* data, const QList<QString>* names = nullptr) override;
    abstractChartView *getRightType() const override;
};

#endif // PIECHARTVIEW_H
