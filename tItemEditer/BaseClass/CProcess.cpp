#include "CProcess.h"
#include <psapi.h>
#include <QDebug>
void *CProcess::getTargetAddr(void *baseAddr, QList<uint> offsets)
{
    /*
     * 应根据当前进程架构分别处理：
     * 自身程序只能编译为64位
     * 若当前进程为64位，直接进行访问
     * 若当前进程为32位，每次获取后都需将高32位置0
     * */

    void*ret = baseAddr;
    void*temp = nullptr;
    SIZE_T bytesRead;
    if (!ReadProcessMemory(m_hProcess, (LPCVOID)baseAddr, &temp, sizeof(temp), &bytesRead)) {
        return nullptr;
    }
    if(m_isWow32){temp = (void*)(((quint64)temp<<32)>>32);}


    for(auto offset:offsets){
        temp = (byte*)temp+offset;
        ret = temp;

        void*temp1 = nullptr;
        if (!ReadProcessMemory(m_hProcess, (LPCVOID)temp, &temp1, sizeof(temp1), &bytesRead)) {
            return nullptr;
        }
        if(m_isWow32){temp = (void*)(((quint64)temp<<32)>>32);}
        temp = temp1;
    }


    return ret;
}

CProcess::CProcess(uint pid,QObject *parent)
    : QObject{parent}
{
    m_hProcess = nullptr;
    initByPid(pid);
}

CProcess::~CProcess()
{
    closeHandle();
}

bool CProcess::initByPid(DWORD pid){
    closeHandle();
    QString processName = "";

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS|PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if(hProcess == nullptr){return false;}

    HMODULE hMod;
    DWORD cbNeeded;

    // 获取进程的模块句柄
    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
        TCHAR szProcessName[MAX_PATH];
        // 获取模块的名称
        if (GetModuleFileNameEx(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR))) {
            processName = QString::fromWCharArray(szProcessName);
        }else{
            return false;
        }
    }else{
        return false;
    }

    BOOL isWow32;
    if (!IsWow64Process(hProcess, &isWow32)) {
        return false;
    }
    m_pname = processName;
    m_pid = pid;
    m_isWow32 = isWow32;
    m_hProcess = hProcess;

    return true;
}

QString CProcess::getProcessNameByPid(DWORD pid)
{
    QString processName = "";
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

    if (hProcess != NULL) {
        HMODULE hMod;
        DWORD cbNeeded;

        // 获取进程的模块句柄
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
            TCHAR szProcessName[MAX_PATH];
            // 获取模块的名称
            if (GetModuleFileNameEx(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR))) {
                processName = QString::fromWCharArray(szProcessName);
            }
        }
        CloseHandle(hProcess);
    }

    return processName;
}

bool CProcess::writeData(void *baseAddr, QList<uint> offsets, size_t writeSize, void *p_value)
{
    return false;
}
