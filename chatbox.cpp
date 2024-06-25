#include "chatbox.h"
#include "ui_chatbox.h"

chatbox::chatbox(QString content,int a,QString id,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatbox)
{
    ui->setupUi(this);
    if(a){

        ui->label->setPixmap(QPixmap(":/new/prefix1/G:/openai-black.png").scaled(ui->label->size()));
    }else {
        ui->label->setPixmap(QPixmap(":/new/prefix1/G:/user.png").scaled(ui->label->size()));
        ui->label->move(1000,20);
        ui->textEdit->move(470,20);
    }
    peoormac=a;
    con = content;
    setAttribute(Qt::WA_StyledBackground, true);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setText(content);ui->textEdit->setMinimumWidth(600);
    ui->textEdit->document()->adjustSize();
    QFont ft;
    ft.setFamily(tr("黑体"));
    ft.setPixelSize(14);
    ui->textEdit->setFont(ft);
    QTextDocument *doc = ui->textEdit->document();
    doc->adjustSize();
    int documentHeight = ui->textEdit->document()->size().height();

    //这个就是你需要的，或者需要进行修正doc->size().rheight() * 1.06

    if (documentHeight >= 100) {
        ui->textEdit->setFixedHeight(documentHeight +30);
        this->setFixedHeight(documentHeight +50);
    } else {
        ui->textEdit->setFixedHeight(documentHeight + 20);
        this->setFixedHeight(documentHeight +40);
    }

    chatid =id;
    qDebug()<<ui->textEdit->size();
}

chatbox::chatbox(QString content, int a)
    : ui(new Ui::chatbox)
{
    ui->setupUi(this);
    if(a){
        ui->label->setPixmap(QPixmap(":/new/prefix1/G:/openai-black.png").scaled(ui->label->size()));
    }else {
        ui->label->setPixmap(QPixmap(":/new/prefix1/G:/user.png").scaled(ui->label->size()));
        ui->label->move(1000,20);
        ui->textEdit->move(470,20);
    }
    peoormac=a;
    con = content;
    setAttribute(Qt::WA_StyledBackground, true);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setText(content);
    ui->textEdit->setMinimumWidth(600);
    ui->textEdit->document()->adjustSize();
    QFont ft;
    ft.setFamily(tr("黑体"));
    ft.setPixelSize(14);
    ui->textEdit->setFont(ft);
    QTextDocument *doc = ui->textEdit->document();
    doc->adjustSize();
    int documentHeight = ui->textEdit->document()->size().height();
    //这个就是你需要的，或者需要进行修正doc->size().rheight() * 1.06
    if (documentHeight >= 100) {
        ui->textEdit->setFixedHeight(documentHeight +30);
        this->setFixedHeight(documentHeight +50);
    } else {
        ui->textEdit->setFixedHeight(documentHeight + 20);
        this->setFixedHeight(documentHeight +40);
    }
 qDebug()<<ui->textEdit->size();
}


chatbox::~chatbox()
{
    delete ui;
}

QString chatbox::getcontent()
{
    return con;
}

int chatbox::getpeoormac()
{
    return peoormac;
}

void chatbox::appendtext(QString c)
{
    ui->textEdit->insertPlainText(c);

    ui->textEdit->document()->adjustSize();
     int documentHeight = ui->textEdit->document()->size().height();
    if (documentHeight >= 100) {
        ui->textEdit->setFixedHeight(documentHeight +30);
        this->setFixedHeight(documentHeight +50);
    } else {
        ui->textEdit->setFixedHeight(documentHeight + 20);
        this->setFixedHeight(documentHeight +40);
    }
}

void chatbox::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton){
        qDebug()<<"h";
    }
}
