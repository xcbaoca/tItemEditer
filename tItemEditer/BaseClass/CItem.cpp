#include "CItem.h"
#include "BaseClass/xGloab.h"
#include <QSqlQuery>
#include <QVariant>


CItem::CItem(QSqlRecord sqlRecord,QObject *parent)
    : QObject{parent}
{
    if(sqlRecord.isEmpty()){return;}
    m_id = sqlRecord.value("id").toUInt();
    m_name = sqlRecord.value("name").toString();
    m_ChnName = sqlRecord.value("Chn_Name").toString();
    m_ChnUrl = sqlRecord.value("Chn_Url").toString();
    m_EngName = sqlRecord.value("Eng_Name").toString();
    m_EngUrl = sqlRecord.value("Eng_Url").toString();
    m_Icon = sqlRecord.value("icon").toByteArray();
}

CItem::CItem(const CItem &other)
{
    m_id=other.m_id;
    m_name = other.m_name;
    m_ChnName = other.m_ChnName;
    m_ChnUrl = other.m_ChnUrl;
    m_EngName = other.m_EngName;
    m_EngUrl = other.m_EngUrl;
    m_Icon = other.m_Icon;
}

CItem &CItem::operator=(const CItem &other)
{
    if(this != &other){
        m_id=other.m_id;
        m_name = other.m_name;
        m_ChnName = other.m_ChnName;
        m_ChnUrl = other.m_ChnUrl;
        m_EngName = other.m_EngName;
        m_EngUrl = other.m_EngUrl;
        m_Icon = other.m_Icon;
    }
    return *this;
}

CItem::~CItem()
{

}

CItem CItem::fromSqlRecord(QSqlRecord sqlRecord,QObject *parent)
{
    return CItem(sqlRecord,parent);
}

CItem CItem::fromTable(quint32 Id, QObject *parent)
{
    QSqlDatabase& db = xGloab::instance().getDb();
    QString sql;
    sql = QString("SELECT * FROM Item WHERE id = %1").arg(Id);
    QSqlQuery query(db);
    query.exec(sql);
    query.next();
    QSqlRecord record = query.record();

    return CItem(record,parent);
}

QSqlRecord CItem::toSqlRecord()
{
    QSqlRecord record = xGloab::instance().getDb().record("item");
    record.setValue("id",m_id);
    record.setValue("name",m_name);
    record.setValue("Chn_Name",m_ChnName);
    record.setValue("Chn_Url",m_ChnUrl);
    record.setValue("Eng_Name",m_EngName);
    record.setValue("Eng_Url",m_EngUrl);
    record.setValue("icon",m_Icon);
    return record;
}
