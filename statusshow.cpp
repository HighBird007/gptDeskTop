#include "statusshow.h"
#include "ui_statusshow.h"

statusshow::statusshow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::statusshow)
{
    ui->setupUi(this);
    QTime current  =QTime::currentTime();
    qDebug()<<current.hour();
    t.setInterval(10000);
    connect(&t,&QTimer::timeout,this,[=]{
        ui->lcdNumber->display(QString::number(current.hour()));
        ui->lcdNumber_2->display(current.minute());
    });
    ui->lcdNumber->display(QString::number(current.hour()));
    ui->lcdNumber_2->display(current.minute());

    t.start();
}

statusshow::~statusshow()
{
    delete ui;
}
