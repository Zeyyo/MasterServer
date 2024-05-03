#pragma once
#include <sal.h>
#include <vector>
#include "conf.h"
#include "Includes/Types/Worker.h"

namespace NetworkLibrary
{
    /// <summary>
    /// Pointer to the ThreadPool instance used for worker management. Initialized to NULL.
    /// </summary>
    inline void* pWorkerThreadPool = nullptr;

    /// <summary>
    /// Mutex for ensuring thread-safe access to the workerThreadPool vector.
    /// </summary>
    inline std::mutex workerThreadPool;

    /// <summary>
    /// Condition variable used to signal when the ThreadPool is initialized and ready to handle requests.
    /// This variable is utilized to synchronize and coordinate the initialization of the ThreadPool
    /// before it begins processing tasks.
    /// </summary>
    inline std::condition_variable coThreadPoolInitialized;

    /// <summary>
    /// Collection of worker instances managed globally.
    /// </summary>
    inline std::vector<Worker> workers;

    /// <summary>
    /// Manages a pool of worker instances, each responsible for loading request handlers
    /// and processing tasks requested by peers in a concurrent manner.
    /// </summary>
    class ThreadPool
    {
    public:
        /// <summary>
        /// Constructs a ThreadPool object with the specified number of worker instances.
        /// </summary>
        /// <param name="numThreads">The number of worker instances to create in the pool.</param>
        ThreadPool(_In_ UINT16 numThreads);

        /// <summary>
        /// Destroys the ThreadPool object and terminates all associated worker instances.
        /// </summary>
        ~ThreadPool();

        /// <summary>
        /// Initializes a specified number of worker instances in the pool.
        /// </summary>
        /// <param name="numWorkers">The number of worker instances to initialize (default is minimum).</param>
        void InitializeIndividualWorkers(_In_ UINT16 numWorkers = WORKER_THREADS_MIN);

        /// <summary>
        /// Terminates a specified number of worker instances in the pool.
        /// </summary>
        /// <param name="numWorkers">The number of worker instances to terminate (default is all).</param>
        void TerminateIndividualWorkers(_In_ UINT16 numWorkers = WORKER_THREADS_ALL);

        /// <summary>
        /// Initializes a worker instance with a communication pipe for status updates.
        /// </summary>
        /// <param name="pipe">The communication pipe for status updates.</param>
        void InitializeWorker(ThreadStatusPipe* pipe);

    private:
        /// <summary>
        /// Spawns a new worker instance with the specified communication pipe.
        /// </summary>
        /// <param name="pipe">The communication pipe for the worker instance.</param>
        std::thread spawn(ThreadStatusPipe* pipe);

        /// <summary>
        /// Collection of worker instances managed by the ThreadPool.
        /// </summary>
        std::vector<Worker> workerInstances_;

        /// <summary>
        /// Flag indicating whether the ThreadPool should stop processing tasks.
        /// </summary>
        bool bStop_;
    };
}