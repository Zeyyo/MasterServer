#include "NEtw_pch.h"
#include "CommandTable.h"
#include <Utilities/CheckRequestFormat/CheckRequestFormat.h>
#include "CommandManager/Commands.h"
#include "Protocols/FTP/config.h"

namespace CommandManager
{
    void RegisterCommands()
    {
        CommandTable::Instance().RegisterCommand(
            SETUP_CALL,
            []() { return std::make_unique<Commands::SetupCall>(); });

        CommandTable::Instance().RegisterCommand(
            FILE_ACQUIRE,
            []() { return std::make_unique<Commands::FileAcquire>(); });

        CommandTable::Instance().RegisterCommand(
            FILE_DISPATCH,
            []() { return std::make_unique<Commands::FileDispatch>(); });
    }
}