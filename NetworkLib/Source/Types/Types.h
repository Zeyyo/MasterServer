#pragma once
#include "pch.h"
#include "Server/config.h"

namespace NetworkLibrary
{
    typedef __int16 PORT;

    struct SessionData
    {
        SessionData(
            std::string szIpAdress, 
            SOCKET socket, 
            sockaddr pAddr) 
            : 
            szIpAdress(szIpAdress), 
            socket(socket), 
            pAddr(pAddr) 
        { }
        std::string szIpAdress;
        SOCKET socket = NULL;
        sockaddr pAddr;
    };

    struct SessionHandlerModule
    {
        void* pModule;
        std::thread thread;
    };

    struct ThreadStatusPipe
    {
        bool bBusy = false;
        std::condition_variable coThreadStatusBusy;
        std::mutex threadStatusMutex;
        bool bAwaitingTermination = false;
        bool* pbWorkerObjectTerminated = NULL;
    };

    enum class ModuleType {
        FTP = FTP_MODULE,
        SMTP = SMTP_MODULE,
        TELNET = TELNET_MODULE,
        _COUNT = 3,
        begin = FTP,
        end = _COUNT

    };

    inline ModuleType operator|(ModuleType a, ModuleType b)
    {
        return static_cast<ModuleType>(static_cast<int>(a) | static_cast<int>(b));
    }
    inline int operator&(ModuleType a, ModuleType b)
    {
        return static_cast<int>(a) & static_cast<int>(b);
    }
}