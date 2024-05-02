#include "pch.h"
#include "ThreadPool.h"

std::thread NetworkLibrary::ThreadPool::spawn(ThreadStatusPipe* pipe) {
	return std::thread([this, pipe] { this->InitializeWorker(pipe); });
}


void NetworkLibrary::ThreadPool::InitializeWorker(ThreadStatusPipe* pipe)
{
	for (;;)
	{
		std::unique_lock<std::mutex> sessionQueuelock(sessoinQueueMutex);
		coThreadContinue.wait(sessionQueuelock, [this, pipe] { return bStop_ || pipe->bAwaitingTermination || !clintSessionQueue.empty(); });

		if (pipe->bAwaitingTermination == true)
		{
			Logger::LOG[Logger::Level::Info] << "Worker terminating!" << Logger::endl;
			*pipe->pbWorkerObjectTerminated = true;
			return;
		}
		if (bStop_ && clintSessionQueue.empty()) return;

		pipe->bBusy = true;
		std::unique_ptr<Session> pSession = std::move(clintSessionQueue.front());
		clintSessionQueue.pop();
		sessionQueuelock.unlock();

		SessionData sessionData = pSession->GetSessionData();
		pSession->fnmRequestTask(sessionData);
		pSession->Close();
		pipe->bBusy = false;
	}
}
void NetworkLibrary::ThreadPool::InitializeIndividualWorkers(UINT16 numWorkers)
{
	for (size_t i = 0; i < numWorkers; i++)
	{
		ThreadStatusPipe* pipe = new ThreadStatusPipe;
		workers.emplace_back(Worker{pipe, spawn(pipe)});
	}
}

void NetworkLibrary::ThreadPool::TerminateIndividualWorkers(UINT16 numWorkers)
{
	if (numWorkers == WORKER_THREADS_ALL)
	{
		for (auto it = workers.begin(); it != workers.end(); ++it) 
			it->stop();
		return;
	}

	int numIterator = 0;
	for (auto it = workers.begin(); it != workers.end(); ++it)
	{
		it->stop();
		numIterator++;
		if (numIterator == numWorkers)
			return;
	}
	return;
}