#include "loginsqlmodel.h"

loginsqlmodel::loginsqlmodel() {

}

void loginsqlmodel::initsql()
{
    sql = QSqlDatabase::addDatabase("QSQLITE","login");
    sql.setDatabaseName("userlogin.db");
    sql.open();
    QSqlQuery query(sql);
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT UNIQUE, "
               "password TEXT, "
               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");
}

QVector<std::pair<QString, QString>> loginsqlmodel::getlastlogin()
{
    initsql();
    QVector<std::pair<QString, QString>> loginList;
    QSqlQuery query(sql);
    query.prepare("SELECT username, password FROM users ORDER BY timestamp DESC");
    if (query.exec()) {
        while (query.next()) {
            QString username = query.value(0).toString();
            QString password = query.value(1).toString();
            loginList.append(qMakePair(username, password));
        }
    } else {
        qDebug() << "Failed to fetch users:" << query.lastError();
    }

    return loginList;
}

void loginsqlmodel::insertnewuser(QString a, QString p)
{
    QSqlQuery query(sql);
    query.prepare("INSERT OR REPLACE INTO users (username, password, timestamp) "
                  "VALUES (:username, :password, CURRENT_TIMESTAMP)");
    query.bindValue(":username", a);
    query.bindValue(":password", p);

    if (!query.exec()) {
        qDebug() << "Failed to insert user:" << query.lastError();
    }
}


loginsqlmodel::~loginsqlmodel()
{
    if(sql.isOpen())sql.close();
}
