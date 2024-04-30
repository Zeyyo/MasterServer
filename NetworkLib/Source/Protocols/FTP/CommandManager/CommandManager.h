#pragma once
#include "pch.h"

#include <memory>
#include <unordered_map>

#include "ICommand.h"
#include "Commands.h"

class CommandManager
{
public:
    CommandManager()
    {
        commands.insert({ "fa", std::make_unique<AcquireFile>() });
        commands.insert({ "fd", std::make_unique<DispatchFile>() });
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
private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
};

