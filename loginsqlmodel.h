#ifndef LOGINSQLMODEL_H
#define LOGINSQLMODEL_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQuery>
#include <QSqlError>

class loginsqlmodel
{
public:
    loginsqlmodel();
    void initsql();
    QVector<std::pair<QString,QString>> getlastlogin();
    void insertnewuser(QString,QString);
    ~loginsqlmodel();
private:
    QSqlDatabase sql;
};

#endif // LOGINSQLMODEL_H
