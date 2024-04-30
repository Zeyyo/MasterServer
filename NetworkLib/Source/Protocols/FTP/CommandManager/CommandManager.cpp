#include "pch.h"
#include "CommandManager.h"

template<typename Func>
bool CommandManager::RunCommand(const std::string name, Func func) const
{
    std::unordered_map<std::string, std::unique_ptr<ICommand>>::const_iterator itCommand = commands.find(name);
    if (itCommand == commands.end())
        return false;

    func(itCommand);
    return true;
}