#ifndef XGLOAB_H
#define XGLOAB_H

#include <QMutex>
#include <QObject>
#include <QSqlDatabase>

class xGloab : public QObject
{
    Q_OBJECT
public:
    static xGloab& instance() {
        // 使用局部静态变量，确保线程安全
        static QMutex mutex;
        mutex.lock();
        static xGloab instance;
        mutex.unlock();
        return instance;
    }

    QSqlDatabase&getDb(){return m_db;};
private:
    QSqlDatabase m_db;

    bool initDatabase();

    explicit xGloab(QObject *parent = nullptr);
    ~xGloab();
signals:
};

#endif // XGLOAB_H
