#ifndef CITEM_H
#define CITEM_H

#include <QObject>

#include <QSqlRecord>

class CItem : public QObject
{
    Q_OBJECT
public:
    explicit CItem(QSqlRecord sqlRecord = QSqlRecord(),QObject *parent = nullptr);
    CItem(const CItem&other);
    CItem& operator=(const CItem &other);
    ~CItem();
    static CItem fromSqlRecord(QSqlRecord sqlRecord,QObject *parent = nullptr);
    static CItem fromTable(quint32 Id,QObject *parent = nullptr);
    QSqlRecord toSqlRecord();

    quint32 m_id=0;
    QString m_name;
    QString m_ChnName;
    QString m_ChnUrl;
    QString m_EngName;
    QString m_EngUrl;
    QByteArray m_Icon;

signals:
};

#endif // CITEM_H
