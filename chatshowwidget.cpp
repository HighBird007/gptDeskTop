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
    if(vec.empty())return arr;
    int sum = 6;
    for(size_t i =vec.size()-1;i>=0&&sum>=0;i--,sum--){
        QJsonObject o;
        if (vec[i]->getpeoormac()==0) {
            // 用户消息
            o["role"] = "user";
        } else {
            // 助手消息
            o["role"] = "assistant";
        }
        qDebug()<<"----------------------------";
        // getcontent() 是获取消息内容的方法
        o["content"] = vec[i]->getcontent();
        arr.append(o);
        if(i==0)break;
    }
    return arr;
}
void chatshowwidget::addnewbox(int b,chatbox *a)
{
    l->insertWidget(b,a);
    vec.push_back(a);
}

