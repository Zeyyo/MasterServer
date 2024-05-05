#include "NEtw_pch.h"

#include "config.h"
#include <map>
#include <sstream>
#include "Types/File.h"

#include "Events/Logger/OstreamLogger.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Events/Exceptions/NetworkOperationExceptions.h"

#include "CommandManager/CommandManager.h"
#include "Server/SessionHandling/Session/Session.h"

#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/CheckRequestFormat/CheckRequestFormat.h"

#include "Utilities/ReceiveHeaderPrefix/ReceiveHeaderPrefix.h"

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
			//int headerLen = Helpers::ReveiveHeaderPrefix(sessionData_.socket);
			Utilities::SocketOperations::Receive(
				sessionData_.socket,
				sInitRequestHeaderBuffer_,
				DEFAULT_HEADER_BASE64_HEADER_LEN);
		}
		catch (Exceptions::NetworkOperationExceptions::FailedToReceiveHeaderPrefixException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReveiveHeaderPrefix()." << Logger::endl;
			// TODO close connection
		}
		catch (Exceptions::NetworkOperationExceptions::InvalidHeaderPrefixException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReveiveHeaderPrefix()." << Logger::endl;
			// TODO close connection
		}
		catch (Exceptions::SocketOperationExceptions::ReceiveTimeOutException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at AcceptRequestHeader()." << Logger::endl;
			// TODO close connection
		}
		catch (Exceptions::SocketOperationExceptions::SocketBufferEmptyException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at AcceptRequestHeader()." << Logger::endl;
		}

		printf("\nData: {%s}\n", sInitRequestHeaderBuffer_);
	}
	
	Header FileTransferHandler::DecryptRequestHeader() const
	{
		std::string kszHeader;
		try
		{
			kszHeader = Crypto::CryptoService().RSADecryptHeader(sInitRequestHeaderBuffer_);
		}
		catch (Exceptions::CryptoOperationException::HeaderDecryptionException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at RSADecryptHeader()." << Logger::endl;
			// TODO failed to decrypt data -> Close connection
		}

		size_t nLength = kszHeader.length();
		Header headerData(kszHeader, nLength);
		return headerData;
	}

	void FileTransferHandler::ExecuteRequestedCommand(Header header)
	{
		std::string szHeaderData = header.headerData;
		std::istringstream ssHeader(szHeaderData);

		if (Utilities::CheckRequestFormat::IsValidRequestPattern(
			Utilities::CheckRequestFormat::ftpPattern_SetupCall,
			szHeaderData))
		{
			// TODO
		}

		if (Utilities::CheckRequestFormat::IsValidRequestPattern(
			Utilities::CheckRequestFormat::ftpPattern_FileAcquire,
			szHeaderData))
		{
			std::string szFileName;
			size_t nFileSize;
			std::string szFileExtension;
			std::string szCommand;
			//std::string szBodyDecryptionKey;

			ssHeader >> szCommand >> szFileName >> nFileSize >> szFileExtension;
			FileData fileData(szFileName, nFileSize, szFileExtension);
			SOCKET socket = sessionData_.socket;
			CommandManager().RunCommand(
				szCommand,
				[&socket, &fileData](CommandManager::CommandIteratorT itCommand)
				{
					itCommand->second->RunCommandSync(socket, fileData);
				});
		}

		if (Utilities::CheckRequestFormat::IsValidRequestPattern(
			Utilities::CheckRequestFormat::ftpPattern_FileDispatch,
			szHeaderData))
		{
			std::string szFileName;
			std::string szCommand;
			ssHeader >> szCommand >> szFileName;

			FileData fileData(szFileName, 0, "");
			SOCKET socket = sessionData_.socket;
			CommandManager().RunCommand(
				szCommand,
				[&socket, &szFileName](CommandManager::CommandIteratorT itCommand)
				{
					itCommand->second->RunCommandSync(socket, szFileName);
				});
		}
		// TODO
		// Invalid header -> Close connection
	}
}