#pragma once
#include "CommandAssociateFunctions/CommandAssociateFunctions.h"
#include "ICommand.h"

class AcquireFile : public ICommand {
public:
    void RunCommandSync(const SOCKET socket, FileData& fileData) override
    {
        Commands::DoFileAcquire(socket, fileData);
    }

    void RunCommandSync(const SOCKET socket, Base64FileData& fileData) override
    {
        Commands::DoFileAcquire(socket, fileData);
    }
};

class DispatchFile : public ICommand {
public:
    void RunCommandSync(const SOCKET socket, std::string& szFileName) override
    {
        Commands::DoFileDispatch(socket, szFileName);
    }
};