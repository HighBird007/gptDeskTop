#include "sqlmodel.h"

sqlmodel &sqlmodel::getlogininstance()
{
    static sqlmodel s("login");
    return s;
}

sqlmodel &sqlmodel::getchatinstance()
{
    static sqlmodel s("chat");
    return s;
}

sqlmodel::sqlmodel(QString str) {
    sql = QSqlDatabase::addDatabase("QSQLITE",str);
    sql.setDatabaseName("useraccount.db");
    sql.open();
}
