#include "chatshowwidget.h"
#include "ui_chatshowwidget.h"

chatshowwidget::chatshowwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatshowwidget)
{
    ui->setupUi(this);
    l= new QVBoxLayout;
    this->setLayout(l);

}

chatshowwidget::~chatshowwidget()
{
    delete ui;
}

void chatshowwidget::addnewbox(chatbox *a)
{
    l->addWidget(a);
    vec.push_back(a);
}

int chatshowwidget::getchatid()
{
    return chatid;
}

void chatshowwidget::setchatid(int a)
{
    chatid =a;
}

QJsonArray chatshowwidget::gethistorymess()
{
    QJsonArray arr;
    if (vec.size() < 6) {
        qDebug()<<"----------------------------";
        for (int i = vec.size()-1; i >=0; i--) {
            qDebug()<<i;
            QJsonObject o;
            if (vec[i]->getpeoormac()==0) {
                // 用户消息
                o["role"] = "user";
            } else {
                // 助手消息
                o["role"] = "assistant";
            }
            qDebug()<<"----------------------------";
            // 假设 getcontent() 是获取消息内容的方法
            o["content"] = vec[i]->getcontent();
            arr.append(o);qDebug()<<"----------------------------";
        }
    }else{
        for (int i = vec.size()-1; i >=vec.size()-6; i--) {
            QJsonObject o;
            if (vec[i]->getpeoormac()==0) {
                // 用户消息
                o["role"] = "user";
            } else {
                // 助手消息
                o["role"] = "assistant";
            }
            // 假设 getcontent() 是获取消息内容的方法
            o["content"] = vec[i]->getcontent();
            arr.append(o);
        }
    }
    qDebug()<<"------------------------------------------";
    qDebug()<<arr;
    qDebug()<<"------------------------------------------";
    return arr;
}
void chatshowwidget::addnewbox(int b,chatbox *a)
{
    l->insertWidget(b,a);
    vec.push_back(a);
}

