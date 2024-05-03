#pragma once
#include <string>
#include <mutex>

namespace NetworkLibrary
{
    struct ThreadStatusPipe
    {
        bool bBusy = false;
        std::condition_variable coThreadStatusBusy;
        std::mutex threadStatusMutex;
        bool bAwaitingTermination = false;
        bool* pbWorkerObjectTerminated = NULL;
    };

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