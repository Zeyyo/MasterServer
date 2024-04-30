#pragma once
#include "pch.h"
#include <io.h>
#include "Events/Logger/OstreamLogger.h"

namespace NetworkLibrary
{
	class Session;
	inline std::queue<NetworkLibrary::Session*> clintSessionQueue;
	inline std::mutex sessoinQueueMutex;
	inline std::condition_variable coThreadContinue;
	
	template<class F>
	void enqueue(F&& client)
	{
		std::unique_lock<std::mutex> lock(sessoinQueueMutex);
		clintSessionQueue.emplace(std::forward<F>(client));
		lock.unlock();
		coThreadContinue.notify_one();
	}

	class Session
	{
	public:
		Session(void(*fnRequestTask)(Session*)) : fnmRequestTask(fnRequestTask)
		{}
		std::string szIpAdress_;
		SOCKET socket_ = NULL;
		sockaddr pAddr_;
		int addrSize_ = sizeof(pAddr_);
		void(*fnmRequestTask)(Session*);
		void CloseAndDestruct();
	};
}