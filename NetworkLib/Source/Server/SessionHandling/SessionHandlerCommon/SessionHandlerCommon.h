#pragma once
#include "Server/SessionHandling/Session/Session.h"
#include <Utilities/SocketOperations/SocketOperations.h>
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Includes/Types/HandlerModule.h"


namespace NetworkLibrary
{
	inline std::vector<SessionHandlerModule> sessionHandlers;


	class SessionHandler
	{
	public:
		SessionHandler(
			UINT8 u8ModuleType,
			PORT port,
			int nBackLog,
			void(*fnRequestTask)(SessionData&))
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
				Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at GetSocket()" << Logger::endl;
			}
			catch (Exceptions::SocketOperationExceptions::BindException& e)
			{
				std::string szErrorMessage = e.GetError();
				Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at BindSocketToLocalAddress()" << Logger::endl;
			}
		}

		void(*fnRequestTask)(SessionData&) = NULL;
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

}