#include "connecttoserve.h"

connecttoserve::connecttoserve() {
    socket=new QTcpSocket;
    connect(socket,&QTcpSocket::readyRead,this,&connecttoserve::readdata);
}

connecttoserve &connecttoserve::getinstance()
{
    static connecttoserve s;
    return s;
}

void connecttoserve::startconnect()
{
  socket->connectToHost("127.0.0.1",52310);
  //socket->connectToHost("139.196.150.195",52310);
    socket->waitForConnected(3000);
}

void connecttoserve::trylogin(QString account, QString password)
{
    QJsonObject login;
    login["type"]="login";
    login["account"]=account;
    login["password"]=password;
    socket->write(QJsonDocument(login).toJson()+"LxTcpOverTag");
}

bool connecttoserve::getloginjudger()
{
    return loginjudger;
}

void connecttoserve::sendtoserve(QJsonDocument doc)
{
    socket->write(doc.toJson()+"LxTcpOverTag");
}

void connecttoserve::gethistory(int id)
{
    QJsonObject o;
    o["type"]="history";
    o["chatId"]=id;
    sendtoserve(QJsonDocument(o));
}

void connecttoserve::getLabels()
{
    QJsonObject o;
    o["type"]="chatLabels";
    sendtoserve(QJsonDocument(o));
}

void connecttoserve::createNewTag()
{
    QJsonObject o;
    o["type"]="createNewTag";
    sendtoserve(QJsonDocument(o));
}

void connecttoserve::deleteTag(int i)
{
    QJsonObject o;
    o["type"]="deleteTag";
    o["id"] = i;
    sendtoserve(QJsonDocument(o));
}

void connecttoserve::readdata()
{
    d.append(socket->readAll());
    while (true) {
        int endOfJson = d.indexOf("LxTcpOverTag");
        if (endOfJson == -1) {
            // 没有找到完整的JSON对象，等待更多数据
            break;
        }
        // 读取实际数据
        QByteArray jsonData = d.left(endOfJson);
        d.remove(0, endOfJson + strlen("LxTcpOverTag"));
        QJsonParseError parseError;
        QJsonDocument data = QJsonDocument::fromJson(jsonData, &parseError);

        if (parseError.error == QJsonParseError::NoError) {
            QJsonObject obj = data.object();
            QString type = obj["type"].toString();
            if (type == "error") {
            } else if (type == "login") {
                emit loginjugder(obj["content"].toBool());
            } else if (type == "chat") {
                emit getdata(obj);
            } else if (type == "history") {
                emit history(obj);
            }  else if(type =="chatLabels"){
                emit chatLabelsdata(obj);
            } else if(type=="createNewTag"){
                emit newTag();
            } else if(type=="chartData"){
                emit chartData(obj);
            }
        }
    }
}


