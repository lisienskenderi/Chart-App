#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include "abstractaxischartview.h"

class barChartView : public abstractAxisChartView{
private:
    QBarSeries* bar;
public:
    barChartView();
    ~barChartView() override;

    QAbstractAxis* getAxi(bool isX) const override;
    bool hasOnlyVAxis() const override;
    void createBarSet(const QString& l) const;
    void appendData(const qreal& v);

    void clearData() override;
    QChart *getChartView(const List<double>* data, const QList<QString>* names = nullptr) override;
    abstractChartView *getRightType() const override;
};

#endif // BARCHARTVIEW_H
