#include "userchart.h"
#include "ui_userchart.h"

userChart::userChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userChart)
{
    ui->setupUi(this);
    initLineChart();

}

userChart::~userChart()
{
    delete ui;
}

void userChart::initLineChart()
{
    QChartView *view = new QChartView(this);
    QChart *c = new QChart();
    view->setChart(c);
    ui->tabWidget->addTab(view,"折线图");
    QLineSeries *s = new QLineSeries(this);

    for(int i = 0 ;i< 10 ;i++){
        s->append(i,QRandomGenerator::global()->bounded(100));
    }
    QValueAxis *axisY = new QValueAxis(this);
    axisY->setRange(0,100);
    axisY->setTitleText("y");
    QCategoryAxis *axisX = new QCategoryAxis(this);
    axisX->append("6/09",0);
    for(int i = 0 ;i<10;i++){
        axisX->append(QString("6/1%1").arg(i),i);
    }
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    c->addAxis(axisX,Qt::AlignBottom);
    c->addAxis(axisY,Qt::AlignLeft);
    c->addSeries(s);
    s->attachAxis(axisX);  // Attach axes to the series
    s->attachAxis(axisY);
}
