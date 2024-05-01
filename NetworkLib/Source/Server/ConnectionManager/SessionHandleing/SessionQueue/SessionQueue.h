#pragma once
#include "pch.h"
#include "Server/ConnectionManager/SessionHandleing/Session/Session.h"

namespace NetworkLibrary
{
	inline std::queue<std::unique_ptr<Session>> clintSessionQueue;
	inline std::mutex sessoinQueueMutex;
	inline std::condition_variable coThreadContinue;

	inline void AddSessionToQueue(std::unique_ptr<Session>&& pSession)
	{
		std::unique_lock<std::mutex> lock(sessoinQueueMutex);
		clintSessionQueue.emplace(std::move(pSession));
		lock.unlock();
		coThreadContinue.notify_one();
	}
}


