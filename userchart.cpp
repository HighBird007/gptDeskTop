#include "userchart.h"
#include "ui_userchart.h"

userChart::userChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userChart)
{
    ui->setupUi(this);
    initLineChart();
    connect(&connecttoserve::getinstance(),&connecttoserve::chartData,this,[=](QJsonObject obj){
        qDebug()<<"------------------";
        QJsonArray arr = obj["data"].toArray();
        qDebug()<<arr;
        QLineSeries *s = new QLineSeries(this);
        QCategoryAxis *axisX = new QCategoryAxis(this);
        axisX->setTitleText("有记录日期");
          QValueAxis *axisY =new QValueAxis(this);
        axisY->setRange(0,200);
        for(int i = 0;i<arr.size();i++){
            QJsonObject o = arr[i].toObject();
            s->append(i,o["usage"].toInt());
            axisX->append(o["date"].toString(),i);
        }
        axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
        c->addSeries(s);
        c->addAxis(axisX,Qt::AlignBottom);
        c->addAxis(axisY,Qt::AlignLeft);
        s->attachAxis(axisX);
        s->attachAxis(axisY);
    });
    QJsonObject o;
    o["type"]="chartData";
    connecttoserve::getinstance().sendtoserve(QJsonDocument(o));
}

userChart::~userChart()
{
    delete ui;
}

void userChart::initLineChart()
{
    view = new QChartView(this);
    c = new QChart();
    view->setChart(c);
    ui->tabWidget->addTab(view,"折线图");
    // QLineSeries *s = new QLineSeries(this);
    // for(int i = 0 ;i< 10 ;i++){
    //     s->append(i,QRandomGenerator::global()->bounded(100));
    // }
    // QValueAxis *axisY = new QValueAxis(this);
    // axisY->setRange(0,100);
    // axisY->setTitleText("y");
    // QCategoryAxis *axisX = new QCategoryAxis(this);
    // axisX->append("6/09",0);
    // for(int i = 0 ;i<10;i++){
    //     axisX->append(QString("6/1%1").arg(i),i);
    // }
    // axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    // c->addAxis(axisX,Qt::AlignBottom);
    // c->addAxis(axisY,Qt::AlignLeft);
    // c->addSeries(s);
    // s->attachAxis(axisX);  // Attach axes to the series
    // s->attachAxis(axisY);
}
