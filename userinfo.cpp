#include "userinfo.h"
#include "ui_userinfo.h"

userInfo::userInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userInfo)
{
    ui->setupUi(this);
    QChartView *chartview =new QChartView;
    ui->tabWidget->addTab(chartview,"折线图");
    QChart *chart = new QChart;
    chartview->setChart(chart);
    QLineSeries *series0=new QLineSeries;
    series0->append(0,2);
    series0->append(1,4);
    series0->append(2,5);
    series0->append(3,1);
    series0->append(4,8);
    series0->append(5,6);
    QCategoryAxis *axisx=new QCategoryAxis;
    axisx->append("6",0);
    axisx->append("6/11",1);
    axisx->append("6/12",2);
    axisx->append("6/13",3);
    axisx->append("6/14",4);
     axisx->append("6/15",5);
    axisx->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    axisx->setTitleText("日期");
     axisx->setRange(0, 5);
    QValueAxis *axisy=new QValueAxis;
    axisy->setRange(0,10);
    axisy->setTitleText("次数");
    chart->addSeries(series0);
    chart->addAxis(axisx,Qt::AlignBottom);
    chart->addAxis(axisy,Qt::AlignLeft);
    series0->attachAxis(axisx);
    series0->attachAxis(axisy);

}

userInfo::~userInfo()
{
    delete ui;
}
