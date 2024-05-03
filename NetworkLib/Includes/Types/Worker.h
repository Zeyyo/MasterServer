#pragma once
#include <string>
#include <mutex>

namespace NetworkLibrary
{
    /// <summary>
    /// Represents a communication pipe used for managing the status of a worker thread.
    /// </summary>
    struct ThreadStatusPipe
    {
        bool bBusy = false;
        std::condition_variable coThreadStatusBusy;
        std::mutex threadStatusMutex;
        bool bAwaitingTermination = false;
        bool* pbWorkerObjectTerminated = NULL;
    };

    /// <summary>
    /// Represents a worker responsible for processing tasks within the ThreadPool.
    /// </summary>
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