#pragma once

#include "pch.h"
#include "config.h"

#include "Types/Types.h"
#include "Events/Logger/OstreamLogger.h"
#include "Protocols/FTP/FTP.h"
#include "SessionHandleing/WorkerPool/ThreadPool.h"
#include "SessionHandleing/SessionHandlerCommon/SessionHandlerCommon.h";

namespace NetworkLibrary
{
    class ConnectionManager
    {
    public:
        ConnectionManager(ModuleType handlerFlags)
        {
            if (workerThreadPool.try_lock())              
                Logger::LOG[Logger::Level::Warning] << "No worker-pool suplied! Sessions will not be handled." << Logger::endl;
            
            if (handlerFlags & ModuleType::FTP) {
                Logger::LOG[Logger::Level::Info] << "FTP flag is set." << Logger::endl;
                SessionHandler *requestModule = new SessionHandler(static_cast<int>(ModuleType::FTP), FILE_TRANSFER_PROTOCOL_PORT, DEFAULT_BACKLOG, ftpMod);
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

        void AddIndividualSessionHandler(int handlerFlags);
        void RemoveIndividualSessionHandler(int handlerFlags);
    private:
        void InitializeConnectionManager();
    };
}