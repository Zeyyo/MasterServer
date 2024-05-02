#pragma once
#include "pch.h"
#include "Types/Types.h"
#include "Events/Logger/OstreamLogger.h"
#include "Server/SessionHandleing/WorkerPool/ThreadPool.h"
#include "Server/SessionHandleing/Session/Session.h"

#include "Utilities/SocketOperations/SocketOperations.h"

using NetworkLibrary::ModuleType;
using NetworkLibrary::PORT;
using NetworkLibrary::Session;

namespace NetworkLibrary
{
	inline std::vector<SessionHandlerModule> sessionHandlers;
}

class SessionHandler
{
public:
	SessionHandler(
		UINT8 u8ModuleType, 
		PORT port,
		int nBackLog, 
		void(*fnRequestTask)(NetworkLibrary::SessionData&)) 
		:
		u8ModuleType_(u8ModuleType),
		fnRequestTask(fnRequestTask)
	{
		try
		{
			socket_ = Utilitis::SocketOperations::GetSocket();
			Utilitis::SocketOperations::BindSocketToLocalAddress(socket_, port, true, nBackLog);
		}
		catch (Exceptions::SocketOperationExceptions::SocketCreationException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at SessionHandler()" << Logger::endl;
		}
		catch (Exceptions::SocketOperationExceptions::BindException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at SessionHandler()" << Logger::endl;
		}
	}

	void(*fnRequestTask)(NetworkLibrary::SessionData&) = NULL;
	DWORD InitializeSessionHandler();
	void stop();
	UINT8 GetModuleType() const;

private:
	bool bStop_ = false;
	SOCKET socket_ = NULL;
	UINT8 u8ModuleType_;
	DWORD AcceptNewConnection(std::unique_ptr<Session>&& clientSession);
	void InitializeConnectionHandler();
	std::thread spawn();
};

