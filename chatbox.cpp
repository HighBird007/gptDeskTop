#include "chatbox.h"
#include "ui_chatbox.h"

chatbox::chatbox(QString content,int a,QWidget *parent)
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
    con = content;
    setAttribute(Qt::WA_StyledBackground, true);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setText(content);
    ui->textEdit->document()->adjustSize();
    ui->textEdit->setFixedWidth(600);
    QFont ft;
    ft.setFamily(tr("黑体"));
    ft.setPixelSize(14);
    ui->textEdit->setFont(ft);

    int documentHeight = ui->textEdit->document()->size().height();
    QTextDocument *doc = ui->textEdit->document();
    doc->adjustSize();  //这一步不能少

    //这个就是你需要的，或者需要进行修正doc->size().rheight() * 1.06

    if (documentHeight >= 100) {
        ui->textEdit->setFixedHeight(documentHeight +30);
        this->setFixedHeight(documentHeight +50);
    } else {
        ui->textEdit->setFixedHeight(documentHeight + 20);
        this->setFixedHeight(documentHeight +40);
    }



}


chatbox::~chatbox()
{
    delete ui;
}

QString chatbox::getcontent()
{
    return con;
}
