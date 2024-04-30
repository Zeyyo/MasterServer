#include "pch.h"
#include "SocketOperations.h"

namespace Utilitis::SocketOperations
{
    SOCKET GetSocket()
    {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET)
        {
            DWORD dwError = WSAGetLastError();
            throw Exceptions::SocketOperationExceptions::SocketCreationException(dwError);
        }
        else
        {
            u_long ulMode = 1;
            ioctlsocket(sock, FIONBIO, &ulMode);
        }
        return sock;
    }

    DWORD BindSocketToLocalAddress(SOCKET socket, NetworkLibrary::PORT port, bool bForListening, int nBacklog)
    {
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        hint.sin_addr.S_un.S_addr = INADDR_ANY; // inet_pton

        int connResult = bind(socket, (sockaddr*)&hint, sizeof(hint));
        if (connResult == SOCKET_ERROR)
        {
            DWORD dwError = WSAGetLastError();
            throw Exceptions::SocketOperationExceptions::BindException(dwError);
        }
        else
            if (bForListening)
                listen(socket, nBacklog);
        
        return 0;
    }

    SOCKET Accept(SOCKET listenSocket, sockaddr pAddr, int addrSize)
    {
        SOCKET clientSocket = NULL;
        for (;;)
        {
            clientSocket = accept(listenSocket, &pAddr, &addrSize);
            if (clientSocket == INVALID_SOCKET)
            {
                DWORD dwError = WSAGetLastError();
                if (dwError == WSAEWOULDBLOCK) continue;
                throw Exceptions::SocketOperationExceptions::AcceptException(dwError);
            }
            return clientSocket;
        }
    }

    int ReceiveDataFromPeer(SOCKET socket, char* prawBuffer, off_t offset, size_t maxLen, int flags)
    {
        int nBytesReceived = recv(socket, prawBuffer + offset, maxLen, flags);
        if (nBytesReceived == SOCKET_ERROR)
        {
            DWORD dwError = WSAGetLastError();
            if (dwError == WSAEWOULDBLOCK) return NULL;
            throw Exceptions::SocketOperationExceptions::ReceiveDataException(dwError);
        }
        return nBytesReceived;
    }

    void Receive(SOCKET socket, char* prawBuffer, size_t nOfBytesToSend, int flags)
    {
        static off_t offset = 0;
        while (offset <= nOfBytesToSend)
        {
            size_t maxLen = nOfBytesToSend - offset;
            int nBytesReceived;
            bool bSuccess = OperationHelper<Exceptions::SocketOperationExceptions::ReceiveDataException>::
                AttemptOperation(3, 300, [&]()
                    {
                        nBytesReceived = ReceiveDataFromPeer(socket, prawBuffer, offset, maxLen, flags);
                    }, [](Exceptions::SocketOperationExceptions::ReceiveDataException) {});
            if (bSuccess == false)
            {
                throw Exceptions::SocketOperationExceptions::ReceiveTimeOutException("");
            }
            if (nBytesReceived == NULL) continue;
            if (nBytesReceived == 0)
            {
                Logger::LOG[Logger::Level::Info] << "Connection has been closed!" << Logger::endl;
                //return CONNECTION_CLOSED;
            }
            if (nBytesReceived > 0)
            {
                Logger::LOG[Logger::Level::Info] << "Data packets received!" << Logger::endl;
                offset += nBytesReceived;
            }
        }
    }

    int SendDataToPeer(SOCKET socket, const char* pkrawBuffer, off_t offset, size_t packetLen, int flags)
    {
        int nBytesSent = send(socket, pkrawBuffer + offset, packetLen, flags);
        if (nBytesSent == SOCKET_ERROR)
        {
            DWORD dwError = WSAGetLastError();
            if (dwError == WSAEWOULDBLOCK) NULL;
            throw Exceptions::SocketOperationExceptions::SendDataException(dwError);
        }
    }

    void Send(SOCKET socket, const char* pkrawBuffer, size_t nOfBytesToSend, int flags)
    {
        static off_t offset = 0;
        while (offset <= nOfBytesToSend)
        {
            size_t packetLen = nOfBytesToSend - offset;
            int nBytesSent;
            bool bSuccess = OperationHelper<Exceptions::SocketOperationExceptions::SendDataException>::
                AttemptOperation(3, 300, [&]()
                    {
                        nBytesSent = SendDataToPeer(socket, pkrawBuffer, offset, packetLen, flags);
                    }, [](Exceptions::SocketOperationExceptions::SendDataException) {});
            if (bSuccess == false)
            {
                throw Exceptions::SocketOperationExceptions::SendTimeOutException("");
            }
            if (nBytesSent == NULL) continue;
            if (nBytesSent >= 0)
            {
                Logger::LOG[Logger::Level::Info] << "Data packets sent!" << Logger::endl;
                offset += nBytesSent;
            }
        }
    }
}