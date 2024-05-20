#pragma once
#include "CommandAssociateFunctions/CommandAssociateFunctions.h"
#include "ICommand.h"
#include "ExtensionManager/ExtensionTable.h"
#include "Events/Exceptions/ExtensionManagerExceptions.h"
#include "Events/Logger/OstreamLogger.h"


namespace CommandManager::Commands
{
    class SetupCall : public ICommand {
    public:
        void Execute(std::istringstream& ssHeader, SOCKET socket) override 
        {
            // TODO: Implement the setup call command logic
        }
    };

    class FileAcquire : public ICommand {
    public:
        void Execute(std::istringstream& ssHeader, SOCKET socket) override
        {
            std::string szCommand, szKey, szIv, szName, szExt;
            std::string szExtensionKey;
            size_t nSize;

            ssHeader >> szCommand >> szKey >> szIv >> szName >> nSize >> szExtensionKey;
            try
            {
                szExt = ExtensionManager::GetExtension(szExtensionKey);
            }
            catch (const Exceptions::ExtensionManagerExceptions::ExtensionKeyMismatch& e)
            {
                std::string szErrorMessage = e.GetError();
                Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at FileAcquire - > GetExtension()." << Logger::endl;
                return;
            }

            Base64FileDataSecure fileData(szName, nSize, szExt, szKey, szIv);
            Commands::DoFileAcquireSecure(socket, fileData);
        }
    };

    class FileDispatch : public ICommand {
    public:
        void Execute(std::istringstream& ssHeader, SOCKET socket) override 
        {
            std::string szCommand, szFileName;

            ssHeader >> szCommand >> szFileName;
            FileData fileData(szFileName, 0, "");

            Commands::DoFileDispatch(socket, szFileName);
        }
    };
}