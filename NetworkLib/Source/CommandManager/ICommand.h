#pragma once
#include "pch.h"
#include "Types/FileTypes.h"

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void RunCommandSync(const SOCKET socket, FileData& fileData) {}
    virtual void RunCommandSync(const SOCKET socket, std::string& szFileName) {}
};

