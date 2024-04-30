#pragma once
#include "pch.h"
#include <string>

#include "Types/Types.h"
#include "Events/Logger/OstreamLogger.h"
#include "Helpers/OperationHelper/OperationHelper.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Events/Exceptions/NetworkOperationExceptions.h"

namespace Utilitis::SocketOperations
{
    SOCKET GetSocket();

    DWORD BindSocketToLocalAddress(
        SOCKET socket, 
        NetworkLibrary::PORT port,
        bool bForListening = false,
        int nBacklog = SOMAXCONN);

    SOCKET Accept(
        SOCKET listenSocket,
        sockaddr pAddr, 
        int addrSize);

    void Receive(
        SOCKET socket,
        char* prawBuffer, 
        size_t nOfBytesToSend,
        int flags = 0);

    void Send(
        SOCKET socket, 
        const char* pkrawBuffer, 
        size_t nOfBytesToSend, 
        int flags = 0);
}