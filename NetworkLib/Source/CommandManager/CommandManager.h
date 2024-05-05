#pragma once
#include "NEtw_pch.h"

#include <memory>
#include <unordered_map>

#include "ICommand.h"
#include "Commands.h"

class CommandManager
{
public:
    CommandManager()
    {
        commands.insert({ szAcquireFileCommand, std::make_unique<AcquireFile>() });
        commands.insert({ szDispatchFileCommand, std::make_unique<DispatchFile>() });
    }

    template<typename Func>
    bool RunCommand(const std::string name, Func func) const
    {
        std::unordered_map<std::string, std::unique_ptr<ICommand>>::const_iterator itCommand = commands.find(name);
        if (itCommand == commands.end())
            return false;

        func(itCommand);
        return true;
    }
    using CommandIteratorT = std::unordered_map<std::string, std::unique_ptr<ICommand>>::const_iterator;
    std::string SetCommandAcquireFile() { return szAcquireFileCommand; };
    std::string SetCommandDispatchFile() { return szDispatchFileCommand; };
private:
    std::string szAcquireFileCommand = "fa";
    std::string szDispatchFileCommand = "fd";

    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
};

