#pragma once
#include "NEtw_pch.h"
#include "Types/File.h"

namespace CommandManager
{
    class ICommand {
    public:
        virtual ~ICommand() = default;
        virtual void Execute(std::istringstream& ssHeader, SOCKET socket) = 0;
    };
}