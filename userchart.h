#ifndef USERCHART_H
#define USERCHART_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QCategoryAxis>
#include <QLineSeries>
#include <QRandomGenerator>
#include <connecttoserve.h>
namespace Ui {
class userChart;
}

class userChart : public QWidget
{
    Q_OBJECT

public:
    explicit userChart(QWidget *parent = nullptr);
    ~userChart();

private:
    Ui::userChart *ui;
    QChartView *view ;
    QChart *c;
private:
    void  initLineChart();
};

#endif // USERCHART_H
