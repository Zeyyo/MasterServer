#pragma once
#include <sal.h>
#include "Includes/Types/HandlerModule.h"

namespace NetworkLibrary
{
    class ConnectionManager
    {
    public:
        ConnectionManager(_In_ ModuleType handlerFlags);
        void AddIndividualSessionHandler(_In_ int handlerFlags);
        void RemoveIndividualSessionHandler(_In_ int handlerFlags);
    private:
        void InitializeConnectionManager();
    };
}