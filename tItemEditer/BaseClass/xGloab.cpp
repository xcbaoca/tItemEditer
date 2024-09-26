#include "xGloab.h"

#include <QCoreApplication>
#include <QFile>


xGloab::xGloab(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}

xGloab::~xGloab()
{
    m_db.close();
}


bool xGloab::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QFile dbFile(":/tItemEditer.db");
    if (!dbFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    // 将数据库文件写入临时位置
    QString tempDbPath = QCoreApplication::applicationDirPath() + "/tempdb.db";
    QFile tempDbFile(tempDbPath);
    if (!tempDbFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    tempDbFile.write(dbFile.readAll());
    tempDbFile.close();
    dbFile.close();

    // 打开数据库
    m_db.setDatabaseName(tempDbPath);
    if (!m_db.open()) {
        return false;
    }

    return true;
}
