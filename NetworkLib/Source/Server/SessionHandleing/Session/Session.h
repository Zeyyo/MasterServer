#pragma once
#include "pch.h"
#include <io.h>
#include "Events/Logger/OstreamLogger.h"
#include "Types/Types.h"

namespace NetworkLibrary
{
	class Session
	{
	public:
		Session(void(*fnRequestTask)(SessionData&)) : fnmRequestTask(fnRequestTask)
		{}
		std::string szIpAdress_;
		SOCKET socket_ = NULL;
		sockaddr pAddr_;
		int addrSize_ = sizeof(pAddr_);
		void(*fnmRequestTask)(SessionData&);
		SessionData GetSessionData() const;
		void Close();
	};
}