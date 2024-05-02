#include "pch.h"
#include "SessionHandlerCommon.h"

void SessionHandler::stop() { bStop_ = true; }

std::thread SessionHandler::spawn() {
    return std::thread([this] { this->InitializeConnectionHandler(); });
}

DWORD SessionHandler::InitializeSessionHandler()
{
    NetworkLibrary::sessionHandlers.emplace_back(NetworkLibrary::SessionHandlerModule{ this, spawn()});
    return 0;
}

DWORD SessionHandler::AcceptNewConnection(std::unique_ptr<Session>&& pClientSession)
{
    for (;;)
    {
        SOCKET clientSocket = Utilitis::SocketOperations::Accept(socket_, pClientSession->pAddr_, pClientSession->addrSize_);
        pClientSession->socket_ = clientSocket;
        
        if (NetworkLibrary::pWorkerThreadPool == NULL)
            Logger::LOG[Logger::Level::Critical] << "No worker-pool suplied! Session will not be handled." << Logger::endl;
        AddSessionToQueue(std::move(pClientSession));
        break;
    }
    return 0;
}

void SessionHandler::InitializeConnectionHandler()
{
    Logger::LOG[Logger::Level::Info] << "Waiting for requests..." << Logger::endl;
    for (;;)
    {
        if (bStop_) break;
        //Session* clientSession = new Session(fnRequestTask);
        auto clientSession = std::make_unique<Session>(fnRequestTask);
        AcceptNewConnection(std::move(clientSession));
    }
}

UINT8 SessionHandler::GetModuleType() const
{
    return u8ModuleType_;
}
