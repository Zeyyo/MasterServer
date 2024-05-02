#include "pch.h"
#include "Session.h"

namespace NetworkLibrary
{

	SessionData Session::GetSessionData() const
	{
		struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&pAddr_;
		struct in_addr ipAddr = pV4Addr->sin_addr;

		char sStr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &ipAddr, sStr, INET_ADDRSTRLEN);
		std::string szIpAddress = std::string(sStr);

		SessionData sessionData(szIpAddress, socket_, pAddr_);
		return sessionData;
	}

	void Session::Close()
	{
		closesocket(socket_);
		Logger::LOG[Logger::Level::Warning] << "Session terminated!" << Logger::endl;
	}
}