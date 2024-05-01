#include "pch.h"
#include "FTP.h"

void ftpMod(NetworkLibrary::SessionData& sessionData)
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << " FTP MOD\n";

	ProtocolHandlers::FTP::FileTransferHandler fileTransferHandler(sessionData);
}

namespace ProtocolHandlers::FTP
{
	void FileTransferHandler::DoInitRequestHandleing()
	{
		Utilitis::SocketOperations::Receive(
			sessionData_.socket,
			sInitRequestBuffer_,
			nInitRequestBufferLen_);

		printf("\nData: %s\n", sInitRequestBuffer_);

		bool bHeaderIsValid = Utilitis::CheckRequestFormat::ValidateRequestPattern(
			Utilitis::CheckRequestFormat::FTPPattern,
			sInitRequestBuffer_);

		if (!bHeaderIsValid)
		{
			// TODO
			std::cout << "Header not valid!";
		}
		DoProcessHeader(sInitRequestBuffer_, nInitRequestBufferLen_);
	}
	
	void FileTransferHandler::DoProcessHeader(const char* pksHeaderBuffer, size_t nHeaderBufferSize)
	{
		std::istringstream ssHeader(pksHeaderBuffer);
		std::string szCommand;
		ssHeader >> szCommand;
		
		
		if (szCommand == "sc")
		{
			// TODO
		}
		if (szCommand == "fa")
		{
			std::string szFileName;
			size_t nFileSize;
			std::string szFileExtension;

			ssHeader >> szFileName >> nFileSize >> szFileExtension;
			FileData fileData(szFileName, nFileSize, szFileExtension);
			SOCKET socket = sessionData_.socket;
			CommandManager().RunCommand(szCommand, [&socket, &fileData](CommandManager::CommandIteratorT itCommand)
				{
					itCommand->second->RunCommandSync(socket, fileData);
				});
		}
		if (szCommand == "fd")
		{
			std::string szFileName;
			ssHeader >> szFileName;

			FileData fileData(szFileName, 0, "");
			SOCKET socket = sessionData_.socket;
			CommandManager().RunCommand(szCommand, [&socket, &szFileName](CommandManager::CommandIteratorT itCommand)
				{
					itCommand->second->RunCommandSync(socket, szFileName);
				});
		}
	}
}