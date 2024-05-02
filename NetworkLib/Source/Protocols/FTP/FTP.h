#pragma once
#include "pch.h"
#include "config.h"

#include <map>
#include <sstream>

#include "Types/FileTypes.h"
#include "Events/Logger/OstreamLogger.h"
#include "CommandManager/CommandManager.h"
#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/CheckRequestFormat/CheckRequestFormat.h"
#include "Server/SessionHandleing/Session/Session.h"

extern void ftpMod(NetworkLibrary::SessionData& sessionData);

namespace ProtocolHandlers::FTP
{
	class FileTransferHandler
	{
	public:
		FileTransferHandler(NetworkLibrary::SessionData& sessionData) :
			sessionData_(sessionData),
			nInitRequestBufferLen_(DEFAULT_RECEIVE_BUFFER_LEN)
		{
			try
			{
				DoInitRequestHandleing();
			}
			catch (Exceptions::SocketOperationExceptions::ReceiveDataException& e)
			{
				std::string szErrorMessage = e.GetError();
				Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at FileTransferHandler()." << Logger::endl;
			}
		}

		void DoInitRequestHandleing();
		void ExecuteRequest(const char* pksHeaderBuffer, size_t headerBufferSize);

		//void DoSetupCallHandleing();
		//void DoFileRequestHandleing();

	private:
		NetworkLibrary::SessionData& sessionData_;
		size_t nInitRequestBufferLen_;
		char sInitRequestBuffer_[DEFAULT_RECEIVE_BUFFER_LEN];
	};
}