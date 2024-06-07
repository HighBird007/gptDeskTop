#ifndef LOGINSQLMODEL_H
#define LOGINSQLMODEL_H

#include "abstractsqlmodel.h"

class loginsqlmodel : public abstractsqlmodel
{
public:
    loginsqlmodel();
    void initsql() override;
    QVector<std::pair<QString,QString>> getlastlogin();
    void insertnewuser(QString,QString);
    ~loginsqlmodel();
};

#endif // LOGINSQLMODEL_H
