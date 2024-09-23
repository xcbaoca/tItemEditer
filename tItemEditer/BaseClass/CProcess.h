#ifndef CPROCESS_H
#define CPROCESS_H

#include <QObject>
#include <Windows.h>

class CProcess : public QObject
{
    Q_OBJECT
private:
    unsigned long m_pid;//进程ID
    QString m_pname;//进程名
    HANDLE m_hProcess;//进程句柄
    bool m_isWow32;//是否位32位进程
public:
    explicit CProcess(uint pid,QObject *parent = nullptr);
    ~CProcess();

    bool initByPid(DWORD pid);
    void closeHandle(){if(m_hProcess!=nullptr){CloseHandle(m_hProcess);}}
    QString getProcessName(){return m_pname;}

    static QString getProcessNameByPid(DWORD pid);

signals:
};

#endif // CPROCESS_H
