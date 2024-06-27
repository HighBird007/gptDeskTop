#ifndef CONNECTTOSERVE_H
#define CONNECTTOSERVE_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVBoxLayout>
class connecttoserve : public QObject
{
    Q_OBJECT
private:
    connecttoserve();
    connecttoserve(const connecttoserve &si)=delete;
    connecttoserve& operator=(const connecttoserve &s)=delete;
    QTcpSocket *socket;
   bool loginjudger=false;
    QByteArray d;

public:
    static connecttoserve &getinstance();
    void startconnect();
    void trylogin(QString account,QString password);
    bool getloginjudger();
    void sendtoserve(QJsonDocument);
    void gethistory(int id);
    void getLabels();
    void createNewTag();
    void deleteTag(int i);
   private slots:
    void   readdata();
   signals:
    void getdata(QJsonObject);
    void loginjugder(bool);
    void history(QJsonObject);
    void chatLabelsdata(QJsonObject);
    void newTag();
    void chartData(QJsonObject);
};
#define start_connect() connecttoserve::getinstance().startconnect();
#define user_login(account,password) connecttoserve::getinstance().trylogin(account,password);
#define singletcpinstance connecttoserve::getinstance();

#endif // CONNECTTOSERVE_H
