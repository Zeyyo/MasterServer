#include "NEtw_pch.h"

#include "config.h"
#include <map>
#include <sstream>
#include "Types/File.h"

#include "Events/Logger/OstreamLogger.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Events/Exceptions/SocketOperationExceptions.h"

#include "CommandManager/CommandManager.h"
#include "Server/SessionHandling/Session/Session.h"

#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/CheckRequestFormat/CheckRequestFormat.h"

#include "Crypto/CryptoService.h"

#include "FTP.h"

void ftpMod(NetworkLibrary::SessionData& sessionData)
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << " FTP MOD\n";

	ProtocolHandlers::FTP::FileTransferHandler fileTransferHandler(sessionData);
}

namespace ProtocolHandlers::FTP
{
	void FileTransferHandler::AcceptRequestHeader()
	{
		try
		{
			Utilitis::SocketOperations::Receive(
				sessionData_.socket,
				sInitRequestHeaderBuffer_,
				nInitRequestBufferLen_);
		}
		catch (Exceptions::SocketOperationExceptions::ReceiveTimeOutException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at DoInitRequestHandleing()." << Logger::endl;
		}
		printf("\nData: %s\n", sInitRequestHeaderBuffer_);
	}
	
	Header FileTransferHandler::DecryptRequestHeader() const
	{
		const char* ksHeader = "";
		try
		{
			ksHeader = Crypto::CryptoService().RSADecryptHeader(sInitRequestHeaderBuffer_);
		}
		catch (Exceptions::CryptoOperationException::HeaderDecryptionException())
		{
			// TODO failed to decrypt data -> Close connection
		}

		size_t nLength = strlen(ksHeader);
		Header headerData(ksHeader, nLength);
		return headerData;
	}

	void FileTransferHandler::ExecuteRequestedCommand(Header header)
	{
		std::string szHeaderData = header.headerData;
		std::istringstream ssHeader(szHeaderData);
		std::string szCommand;
		std::string szBodyDecryptionKey;

		ssHeader >> szBodyDecryptionKey;
		ssHeader >> szCommand;
		
		if (Utilitis::CheckRequestFormat::IsValidRequestPattern(
			Utilitis::CheckRequestFormat::ftpPattern_SetupCall,
			szHeaderData))
		{
			// TODO
		}

		if (Utilitis::CheckRequestFormat::IsValidRequestPattern(
			Utilitis::CheckRequestFormat::ftpPattern_FileAcquire,
			szHeaderData))
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
			szHeaderData))
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
		// Invalid header -> Close connection
	}
}