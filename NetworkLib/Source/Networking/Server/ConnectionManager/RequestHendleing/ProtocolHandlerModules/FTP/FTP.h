#pragma once
#include "pch.h"
#include "config.h"

#include <map>
#include <sstream>

#include "Networking/Types/FileTypes.h"
#include "FileTransfer/FileTransferOperations.h"

#include "Events/Logger/OstreamLogger.h"
#include "Networking/Utilities/SocketEvents.h"
#include "Networking/Utilities/SocketUtils.h"
#include "Networking/Server/ConnectionManager/SessionHandleing/Session/Session.h"

#include "Networking/Utilities/SocketUtils.h"
#include "Networking/Utilities/SocketOperations/SocketOperations.h"

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
		void DoFileAcquire(FileData& fileData);
		void DoFileDispatch(SOCKET socket, std::string szFileName);

	private:
		NetworkLibrary::Session* pSession_ = NULL;
		size_t nInitRequestBufferLen_;
		char sInitRequestBuffer_[DEFAULT_RECEIVE_BUFFER_LEN];
	};
}