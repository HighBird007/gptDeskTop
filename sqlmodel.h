#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
class sqlmodel
{
    Q_OBJECT
public:
    static sqlmodel& getlogininstance();
    static sqlmodel& getchatinstance();
private:
    QSqlDatabase sql;
private:
     sqlmodel(QString);

};

#endif // SQLMODEL_H
