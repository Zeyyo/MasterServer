#pragma once
#include "Types/Session.h"

namespace Utilities::SocketOperations
{
    SOCKET GetSocket();

    DWORD BindSocketToLocalAddress(
        SOCKET socket, 
        NetworkLibrary::PORT port,
        bool bForListening = false,
        int nBacklog = SOMAXCONN);

    SOCKET Accept(
        SOCKET listenSocket,
        sockaddr& pAddr, 
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

    WORD ReceiveHeaderFromPeer(
        SOCKET socket,
        char* prawBuffer,
        size_t nOfBytesToReceive,
        int flags = 0);

    WORD ReceiveFileFromPeer(
        SOCKET socket,
        char* prawBuffer,
        size_t nOfBytesToReceive,
        int flags = 0);
}