#pragma once
#include "pch.h"

#include <memory>
#include <unordered_map>

#include "ICommand.h"

class CommandManager
{
public:
    CommandManager()
    {
        commands.insert({ "AcquireFile", std::make_unique<AcquireFile>() });
        commands.insert({ "DispatchFile", std::make_unique<DispatchFile>() });
    }

    template<typename Func>
    bool RunCommand(const std::string name, Func func) const;

    using CommandIteratorT = std::unordered_map<std::string, std::unique_ptr<ICommand>>::const_iterator;
private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
};

