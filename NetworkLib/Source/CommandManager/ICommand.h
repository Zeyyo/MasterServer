#pragma once
#include "NEtw_pch.h"
#include "Types/File.h"

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void RunCommandSync(const SOCKET socket, FileData& fileData) {}
    virtual void RunCommandSync(const SOCKET socket, Base64FileData& fileData) {}
    virtual void RunCommandSync(const SOCKET socket, std::string& szFileName) {}
};

