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

protected:
    QSqlDatabase sql;

};

#endif // ABSTRACTSQLMODEL_H
