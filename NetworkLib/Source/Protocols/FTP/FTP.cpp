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

		// Decrypt the sInitRequestBuffer_ -> check if it is a valid header format...
		ExecuteRequest(sInitRequestBuffer_, nInitRequestBufferLen_);
	}
	
	void FileTransferHandler::ExecuteRequest(const char* pksHeaderBuffer, size_t nHeaderBufferSize)
	{
		std::istringstream ssHeader(pksHeaderBuffer);
		std::string szCommand;
		ssHeader >> szCommand;
		
		if (Utilitis::CheckRequestFormat::IsValidRequestPattern(
			Utilitis::CheckRequestFormat::ftpPattern_FileAcquire,
			sInitRequestBuffer_))
		{
			// TODO
		}
		if (Utilitis::CheckRequestFormat::IsValidRequestPattern(
			Utilitis::CheckRequestFormat::ftpPattern_FileAcquire,
			sInitRequestBuffer_))
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
		if (Utilitis::CheckRequestFormat::IsValidRequestPattern(
			Utilitis::CheckRequestFormat::ftpPattern_FileDispatch,
			sInitRequestBuffer_))
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
		// TODO
		// Invalid header
	}
}