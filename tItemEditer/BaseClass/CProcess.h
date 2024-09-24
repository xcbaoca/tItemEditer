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

    void*getTargetAddr(void*baseAddr,QList<uint>offsets);
public:
    explicit CProcess(uint pid,QObject *parent = nullptr);
    ~CProcess();

    bool initByPid(DWORD pid);
    bool isInited(){return m_hProcess!=nullptr;}
    void closeHandle(){if(m_hProcess!=nullptr){CloseHandle(m_hProcess);m_hProcess=nullptr;}}
    QString getProcessName(){return m_pname;}

    static QString getProcessNameByPid(DWORD pid);

    void readData(void*baseAddr,QList<uint>offsets);
    bool writeData(void*baseAddr,QList<uint>offsets,size_t writeSize,void*p_value);

signals:
};

#endif // CPROCESS_H
