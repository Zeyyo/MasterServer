#include "NEtw_pch.h"

#include "Server/config.h"

#include "Includes/Types/HandlerModule.h"
#include "Events/Logger/OstreamLogger.h"
#include "Protocols/FTP/FTP.h"
#include "Includes/WorkerPool.h"
#include "Server/SessionHandling/SessionHandlerCommon/SessionHandlerCommon.h";

#include "Includes/ConnectionManager.h"

namespace NetworkLibrary
{
    ConnectionManager::ConnectionManager(ModuleType handlerFlags)
    {
        if (workerThreadPool.try_lock())
            Logger::LOG[Logger::Level::Warning] << "No worker-pool suplied! Sessions will not be handled." << Logger::endl;

        if (handlerFlags & ModuleType::FTP) {
            Logger::LOG[Logger::Level::Info] << "FTP flag is set." << Logger::endl;
            SessionHandler* requestModule = new SessionHandler(static_cast<int>(ModuleType::FTP), FILE_TRANSFER_PROTOCOL_PORT, DEFAULT_BACKLOG, ftpMod);
            requestModule->InitializeSessionHandler();
        }

        if (handlerFlags & ModuleType::SMTP)
        {
            Logger::LOG[Logger::Level::Info] << "SMTP flag is set." << Logger::endl;
        }

        if (handlerFlags & ModuleType::TELNET)
        {
            Logger::LOG[Logger::Level::Info] << "TELNET flag is set." << Logger::endl;
        }
    }

    void NetworkLibrary::ConnectionManager::InitializeConnectionManager()
    {

    }

    void NetworkLibrary::ConnectionManager::AddIndividualSessionHandler(int handlerFlags)
    {
        SessionHandler* pSessionHandler = new SessionHandler(handlerFlags, FILE_TRANSFER_PROTOCOL_PORT, DEFAULT_BACKLOG, ftpMod);
        pSessionHandler->InitializeSessionHandler();
    }

    void NetworkLibrary::ConnectionManager::RemoveIndividualSessionHandler(int handlerFlag)
    {
        for (auto it = sessionHandlers.begin(); it != sessionHandlers.end(); ++it)
        {
            SessionHandler* pModule = reinterpret_cast<SessionHandler*>(it->pModule);
            if (pModule->GetModuleType() == handlerFlag) pModule->stop();
        }
    }
}
