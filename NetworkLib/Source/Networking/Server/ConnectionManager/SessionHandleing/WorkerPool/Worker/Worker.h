#pragma once
#include "pch.h"
#include "Networking/Server/ConnectionManager/SessionHandleing/WorkerPool/ThreadPool.h"
#include "Networking/Types/Types.h"

namespace NetworkLibrary
{
    class Worker
    {
    public:
        ThreadStatusPipe* pipe = NULL;
        std::thread thread;
        bool bAwaitingTermination = false;
        bool bTerminated = false;
        void stop();
    };
}