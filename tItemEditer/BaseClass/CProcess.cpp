#include "CProcess.h"
#include <psapi.h>
#include <QDebug>
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
