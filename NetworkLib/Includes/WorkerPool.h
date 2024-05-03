#pragma once
#include <vector>
#include "conf.h"
#include "Includes/Types/Worker.h"

namespace NetworkLibrary
{
	class ThreadPool;
	//class Worker;

	inline void* pWorkerThreadPool = NULL;
	inline std::mutex workerThreadPool;
	inline std::condition_variable coThreadPoolInitialized;
	inline std::vector<Worker> workers;

	class ThreadPool
	{
	public:
		ThreadPool(UINT16 numThreads);
		~ThreadPool();

		void InitializeIndividualWorkers(UINT16 numWorkers = WORKER_THREADS_MIN);
		void TerminateIndividualWorkers(UINT16 numWorkers = WORKER_THREADS_ALL);
		void InitializeWorker(ThreadStatusPipe* pipe);

	private:
		std::thread spawn(ThreadStatusPipe* pipe);
		std::vector<std::thread> workerThreads_;
		bool bStop_;
	};
}