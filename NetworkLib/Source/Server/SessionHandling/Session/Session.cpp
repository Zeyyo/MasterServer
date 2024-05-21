#include "NEtw_pch.h"

#include <io.h>
#include "Events/Logger/OstreamLogger.h"
#include "Events/Exceptions/ConnectionManagerExceptions.h"

#include "Utilities/NameMangling/NameMangling.h"

#include "Session.h"
#include "sstream"

namespace NetworkLibrary
{
	void GetInAddrInfo(const sockaddr* saGNI, char* hostAddr, char* hostName, char* servInfo)
	{
		DWORD dwRetval = getnameinfo(saGNI,
			(saGNI->sa_family == AF_INET) ? sizeof(sockaddr_in) : sizeof(sockaddr_in6),
			hostName,
			NI_MAXHOST,
			servInfo,
			NI_MAXSERV,
			NI_NUMERICSERV);

		if (dwRetval != 0)
			throw Exceptions::ConnectionManagerExceptions::GetPeerInfoException(dwRetval);

		if (saGNI->sa_family == AF_INET) {
			// IPv4
			const sockaddr_in* pV4Addr = reinterpret_cast<const sockaddr_in*>(saGNI);
			inet_ntop(AF_INET, &(pV4Addr->sin_addr), hostAddr, NI_MAXHOST);
		}
		else if (saGNI->sa_family == AF_INET6) {
			// IPv6
			const sockaddr_in6* pV6Addr = reinterpret_cast<const sockaddr_in6*>(saGNI);
			inet_ntop(AF_INET6, &(pV6Addr->sin6_addr), hostAddr, NI_MAXHOST);
		}
		else { throw Exceptions::ConnectionManagerExceptions::GetPeerAddrException(WSAEAFNOSUPPORT); }
	}

	std::string GetPeerAddrPlaceholder()
	{
		std::string szPeerGetAddrInfoFail = "Peer_Connected_at";
		Utilities::NameMangling::PeerPlaceholderSuffixMangle(szPeerGetAddrInfoFail);
		return szPeerGetAddrInfoFail;
	}

	SessionData Session::GetSessionData() const 
	{
		char hostAddr[NI_MAXHOST];
		char hostName[NI_MAXHOST];
		char servInfo[NI_MAXSERV];

		std::string szIpAddress;
		std::string szHostName;
		std::string szServInfo;
		try
		{
			GetInAddrInfo((sockaddr*)&pAddr_, hostAddr, hostName, servInfo);
			szIpAddress = std::string(hostAddr);
			szHostName = std::string(hostName);
			szServInfo = std::string(servInfo);
		}
		catch (const Exceptions::ConnectionManagerExceptions::GetPeerInfoException& e)
		{
			szIpAddress = GetPeerAddrPlaceholder();
			szHostName = "N/A";
			szServInfo = "N/A";

			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage 
				<< " Exception thrown at GetSessionData - > GetInAddrInfo()." << Logger::endl;
		}
		catch (const Exceptions::ConnectionManagerExceptions::GetPeerAddrException& e)
		{
			szIpAddress = GetPeerAddrPlaceholder();
			szHostName = "N/A";
			szServInfo = "N/A";

			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage 
				<< " Exception thrown at GetSessionData - > GetInAddrInfo()." << Logger::endl;
		}

		SessionData sessionData(szIpAddress, szHostName, szServInfo, socket_, pAddr_);
		return sessionData;
	}

	void Session::Close()
	{
		closesocket(socket_);
		Logger::LOG[Logger::Level::Warning] << "Session terminated!" << Logger::endl;
	}
}