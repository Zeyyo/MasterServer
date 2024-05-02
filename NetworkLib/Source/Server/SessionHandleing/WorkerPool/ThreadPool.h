#pragma once
#include "pch.h"
#include "config.h"

#include "Worker/Worker.h"
#include "Types/Types.h"
#include "Events/Logger/OstreamLogger.h"
#include "Server/SessionHandleing/Session/Session.h"
#include "Server/SessionHandleing/SessionQueue/SessionQueue.h"


namespace NetworkLibrary
{
	class ThreadPool;
	class Worker;

	inline void* pWorkerThreadPool = NULL;
	inline std::mutex workerThreadPool;
	inline std::condition_variable coThreadPoolInitialized;
	inline std::vector<Worker> workers;

	class ThreadPool
	{
	public:
		ThreadPool(UINT16 numThreads) : bStop_(false)
		{
			InitializeIndividualWorkers(numThreads);
			pWorkerThreadPool = this;
			workerThreadPool.lock();
		}

		~ThreadPool()
		{
			std::unique_lock<std::mutex> lock(sessoinQueueMutex);
			pWorkerThreadPool = NULL;
			bStop_ = true;
			coThreadContinue.notify_all();
			TerminateIndividualWorkers();
			lock.unlock();
			/*for (std::thread& worker : workerThreads_)
				worker.join();*/
		}

		void InitializeIndividualWorkers(UINT16 numWorkers = WORKER_THREADS_MIN);
		void TerminateIndividualWorkers(UINT16 numWorkers = WORKER_THREADS_ALL);
		void InitializeWorker(ThreadStatusPipe* pipe);

	private:
		std::thread spawn(ThreadStatusPipe* pipe);
		std::vector<std::thread> workerThreads_;
		bool bStop_;
	};
}