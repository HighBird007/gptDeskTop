#ifndef CHATLOGINMODEL_H
#define CHATLOGINMODEL_H

#include "abstractsqlmodel.h"

class chatloginmodel
{
public:
    void initsql();
    chatloginmodel();
    QSqlDatabase sql;
    void insertchat(QString content,int peoormac);
};

#endif // CHATLOGINMODEL_H
