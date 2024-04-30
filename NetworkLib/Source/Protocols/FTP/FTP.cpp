#include "pch.h"
#include "FTP.h"

void ftpMod(NetworkLibrary::Session* pSession)
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << " FTP MOD\n";

	ProtocolHandlers::FTP::FileTransferHandler fileTransferHandler(pSession);

}

namespace ProtocolHandlers::FTP
{
	void FileTransferHandler::DoInitRequestHandleing()
	{
		Utilitis::SocketOperations::Receive(pSession_->socket_, sInitRequestBuffer_, nInitRequestBufferLen_);
		printf("\nData: %s\n", sInitRequestBuffer_);

		DoProcessHeader(sInitRequestBuffer_, nInitRequestBufferLen_);
	}
	
	void FileTransferHandler::DoProcessHeader(const char* pksHeaderBuffer, size_t nHeaderBufferSize)
	{
		std::istringstream ssHeader(pksHeaderBuffer);
		std::string szCommand;
		ssHeader >> szCommand;
		
		CommandManager().RunCommand(szCommand, [a, b](CommandManager::CommandIteratorT itCommand)
			{
				itCommand->second->RunCommandSync();
			});

		if (operation == "sc")
		{
			// TODO
		}
		if (operation == "fa")
		{
			std::string szFileName;
			size_t nFileSize;
			std::string szFileExtension;

			ssHeader >> szFileName >> nFileSize >> szFileExtension;
			FileData fileData(szFileName, nFileSize, szFileExtension);
			DoFileAcquire(fileData);
		}
		if (operation == "fd")
		{
			std::string szFileName;
			ssHeader >> szFileName;

			FileData fileData(szFileName, 0, "");
			DoFileDispatch(pSession_->socket_, szFileName);
		}
	}
}