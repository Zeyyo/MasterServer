#pragma once
#include "Types/Session.h"

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