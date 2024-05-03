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
}