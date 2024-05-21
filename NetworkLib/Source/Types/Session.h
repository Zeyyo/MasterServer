#pragma once
#include <string>
#include <thread>
namespace NetworkLibrary
{
    typedef __int16 PORT;

    typedef SOCKET;
    typedef sockaddr;

    struct SessionData
    {
        SessionData(
            std::string szIpAdress,
            std::string szHostName,
            std::string szServInfo,
            SOCKET socket,
            sockaddr pAddr)
            :
            szIpAdress(szIpAdress),
            szHostName(szHostName),
            szServInfo(szServInfo),
            socket(socket),
            pAddr(pAddr)
        { }
        std::string szIpAdress;
        std::string szHostName;
        std::string szServInfo;
        SOCKET socket = NULL;
        sockaddr pAddr;
    };

    struct SessionHandlerModule
    {
        void* pModule;
        std::thread thread;
    };
}