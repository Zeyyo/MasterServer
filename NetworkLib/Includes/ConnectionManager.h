#pragma once
#include "Includes/Types/HandlerModule.h"

namespace NetworkLibrary
{
    class ConnectionManager
    {
    public:
        ConnectionManager(ModuleType handlerFlags);
        void AddIndividualSessionHandler(int handlerFlags);
        void RemoveIndividualSessionHandler(int handlerFlags);
    private:
        void InitializeConnectionManager();
    };
}