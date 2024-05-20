#pragma once
#include "Types/Header.h"
#include "Types/Session.h"

#include "config.h"
#include "CommandManager/CommandTable.h"
#include "ExtensionManager/ExtensionTable.h"

#include <map>

extern void ftpMod(NetworkLibrary::SessionData& sessionData);

namespace ProtocolHandlers::FTP
{
	class FileTransferHandler
	{
	public:
		FileTransferHandler(
			NetworkLibrary::SessionData& sessionData) 
			:
			sessionData_(sessionData),
			nInitRequestBufferLen_(DEFAULT_RECEIVE_BUFFER_LEN)
		{
			CommandManager::RegisterCommands();
			ExtensionManager::RegisterExtensions();
		}
		void ProcessRequest();
		Header AcceptRequestHeader();
		void ExecuteRequestedCommand(Header);

		//void DoSetupCallHandleing();
		//void DoFileRequestHandleing();

	private:
		NetworkLibrary::SessionData& sessionData_;
		size_t nInitRequestBufferLen_;
		char sInitRequestHeaderBuffer_[DEFAULT_RECEIVE_BUFFER_LEN] = "";

	};
}