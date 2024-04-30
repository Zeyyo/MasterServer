#pragma once
#include "pch.h"
#include "CommandAssociateFunctions/CommandAssociateFunctions.h"
#include "ICommand.h"

class AcquireFile : public ICommand {
public:
    void RunCommandSync(SOCKET socket, FileData& fileData) override
    {
        Commands::DoFileAcquire(socket, fileData);
    }
};

class DispatchFile : public ICommand {
public:
    void RunCommandSync(SOCKET socket, std::string& szFileName) override
    {
        Commands::DoFileDispatch(socket, szFileName);
    }
};