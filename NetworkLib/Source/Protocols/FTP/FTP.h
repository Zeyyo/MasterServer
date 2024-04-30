#pragma once
#include "pch.h"
#include "config.h"

#include <map>
#include <sstream>

#include "Types/FileTypes.h"
#include "Events/Logger/OstreamLogger.h"
#include "Utilities/SocketOperations/SocketOperations.h"
#include "CommandManager/CommandManager.h"
#include "Server/ConnectionManager/SessionHandleing/Session/Session.h"

extern void ftpMod(NetworkLibrary::Session* session);

namespace ProtocolHandlers::FTP
{
	class FileTransferHandler
	{
	public:
		FileTransferHandler(NetworkLibrary::Session* pSession) : 
			pSession_(pSession),
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
		void DoProcessHeader(const char* pksHeaderBuffer, size_t headerBufferSize);

		//void DoSetupCallHandleing();
		//void DoFileRequestHandleing();

	private:
		NetworkLibrary::Session* pSession_ = NULL;
		size_t nInitRequestBufferLen_;
		char sInitRequestBuffer_[DEFAULT_RECEIVE_BUFFER_LEN];
	};
}