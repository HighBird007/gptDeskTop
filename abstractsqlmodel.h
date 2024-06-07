#ifndef ABSTRACTSQLMODEL_H
#define ABSTRACTSQLMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQuery>
#include <QSqlError>
class abstractsqlmodel
{

public:
    abstractsqlmodel();
   virtual void initsql() = 0;

protected:
    QSqlDatabase sql;

};

#endif // ABSTRACTSQLMODEL_H
