#include "connecttoserve.h"

connecttoserve::connecttoserve() {
    socket=new QTcpSocket;
    connect(socket,&QTcpSocket::readyRead,this,&connecttoserve::readdata);
    connect(socket,&QTcpSocket::connected,this,[](){
        qDebug()<<"okoko";
    });
    connect(socket,&QTcpSocket::disconnected,this,[](){
        qDebug()<<"nononon";
    });
}

connecttoserve &connecttoserve::getinstance()
{
    static connecttoserve s;
    return s;
}

void connecttoserve::startconnect()
{
   //socket->connectToHost("127.0.0.1",52310);
   socket->connectToHost("139.196.150.195",52310);
   // socket->open(QIODevice::ReadWrite);
    socket->waitForConnected(3000);
    qDebug()<<socket->error()<<"???";
}

void connecttoserve::trylogin(QString account, QString password)
{
    QJsonObject login;
    login["type"]="login";
    login["account"]=account;
    login["password"]=password;
    socket->write(QJsonDocument(login).toJson());
}

bool connecttoserve::getloginjudger()
{
    return loginjudger;
}

void connecttoserve::sendtoserve(QJsonDocument doc)
{
    socket->write(doc.toJson());
}

void connecttoserve::readdata()
{
    qDebug()<<"new mess";
    d.append(socket->readAll());
    QJsonDocument data=QJsonDocument::fromJson(d);
    if(data.isNull()){
        return ;
    }else {
        d.clear();
    }
    QJsonObject obj=data.object();
    QString type=obj["type"].toString();
    if(type=="error"){
        qDebug()<<obj["content"].toString();
    }
    if(type=="login"){emit loginjugder(obj["content"].toBool())  ;return ;}
    if(type=="chat"){
        emit getdata(obj);
        return ;
    }
    if(type=="history"){
        qDebug()<<"hist";
        emit history(obj);
        return ;
    }
}


