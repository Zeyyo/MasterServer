#pragma once
#include "CommandAssociateFunctions/CommandAssociateFunctions.h"
#include "ICommand.h"

namespace CommandManager::Commands
{
    class SetupCall : public ICommand {
    public:
        void Execute(std::istringstream& ssHeader, SOCKET socket) override {
            // TODO: Implement the setup call command logic
        }
    };

    class FileAcquire : public ICommand {
    public:
        void Execute(std::istringstream& ssHeader, SOCKET socket) override {
            std::string szCommand, szKey, szIv, szFileName;
            size_t nFileSize;
            std::string szFileExtension;

            ssHeader >> szCommand >> szKey >> szIv >> szFileName >> nFileSize >> szFileExtension;
            Base64FileDataSecure fileData(szFileName, nFileSize, szFileExtension, szKey, szIv);

            Commands::DoFileAcquireSecure(socket, fileData);

            /*CommandManager().RunCommand(
                szCommand,
                [&socket, &fileData](CommandManager::CommandIteratorT itCommand) {
                    itCommand->second->RunCommandSync(socket, fileData);
                });*/
        }
    };

    class FileDispatch : public ICommand {
    public:
        void Execute(std::istringstream& ssHeader, SOCKET socket) override {
            std::string szCommand, szFileName;
            ssHeader >> szCommand >> szFileName;

            FileData fileData(szFileName, 0, "");

            Commands::DoFileDispatch(socket, szFileName);


            /*CommandManager().RunCommand(
                szCommand,
                [&socket, &szFileName](CommandManager::CommandIteratorT itCommand) {
                    itCommand->second->RunCommandSync(socket, szFileName);
                });*/
        }
    };
}