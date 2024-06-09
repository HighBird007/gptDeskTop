#include "chatloginmodel.h"


void chatloginmodel::initsql()
{
    sql = QSqlDatabase::addDatabase("QSQLITE");
    sql.setDatabaseName("userchat.db");
    if (!sql.open()) {
        qDebug() << "Error: connection with database failed";
        return;
    }

    QSqlQuery query(sql);

    if (!query.exec("CREATE TABLE IF NOT EXISTS chatcontent ("
                    "id INTEGER NOT NULL CONSTRAINT chatcontent_pk PRIMARY KEY AUTOINCREMENT, "
                    "typeid INTEGER NOT NULL, "
                    "content TEXT NOT NULL, "
                    "ispeo INTEGER NOT NULL, "
                    "timestamp DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP);")) {
        qDebug() << "Failed to create table:" << query.lastError().text();
    }

    if (!query.exec("CREATE INDEX IF NOT EXISTS chatcontent_id_index ON chatcontent (id);")) {
        qDebug() << "Failed to create index on id:" << query.lastError().text();
    }

    if (!query.exec("CREATE INDEX IF NOT EXISTS chatcontent_timestamp_index ON chatcontent (timestamp);")) {
        qDebug() << "Failed to create index on timestamp:" << query.lastError().text();
    }

    if (!query.exec("CREATE INDEX IF NOT EXISTS chatcontent_typeid_index ON chatcontent (typeid);")) {
        qDebug() << "Failed to create index on typeid:" << query.lastError().text();
    }
}

chatloginmodel::chatloginmodel() {
    initsql();
}

void chatloginmodel::insertchat(QString content, int peoormac)
{
    QSqlQuery query(sql);
    query.prepare("INSERT INTO chatcontent (typeid, content, ispeo) "
                  "VALUES (:typeid, :content, :ispeo)");

    query.bindValue(":typeid", 1);
    query.bindValue(":content", content);
    query.bindValue(":ispeo", peoormac);

    if(!query.exec()) {
        qDebug() << "Error inserting into chatcontent:" << query.lastError().text();
    } else {
        qDebug() << "Insert successful!";
    }
}
