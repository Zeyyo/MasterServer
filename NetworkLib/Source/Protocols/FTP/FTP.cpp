#include "NEtw_pch.h"

#include "config.h"
#include <map>
#include <sstream>
#include "Types/File.h"

#include "Events/Logger/OstreamLogger.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Events/Exceptions/NetworkOperationExceptions.h"

#include "Server/SessionHandling/Session/Session.h"

#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/CheckRequestFormat/CheckRequestFormat.h"
#include "Utilities/Packing/Packing.h"

#include "Crypto/CryptoService.h"

#include "FTP.h"

void ftpMod(NetworkLibrary::SessionData& sessionData)
{
	std::cerr << " FTP MOD\n";

	ProtocolHandlers::FTP::FileTransferHandler fileTransferHandler(sessionData);
	fileTransferHandler.ProcessRequest();
}

namespace ProtocolHandlers::FTP
{
	void FileTransferHandler::ProcessRequest()
	{
		Header header = AcceptRequestHeader();
		ExecuteRequestedCommand(header);
	}

	Header FileTransferHandler::AcceptRequestHeader()
	{
		bool success = Utilities::SocketOperations::ReceiveHeaderFromPeer(sessionData_.socket,
			sInitRequestHeaderBuffer_,
			DEFAULT_HEADER_BASE64_HEADER_LEN);
		if (!success)
			// TODO close conn
			std::cout << "\nfailed to get header\n";

		printf("\nData: {%s}\n", sInitRequestHeaderBuffer_);

		Header header;
		success = Utilities::Packing::UnpackHeaderSecure(sInitRequestHeaderBuffer_, header);
		if (!success)
			// TODO close conn
			std::cout << "\nfailed to unpack header\n";
		return header;
	}

	void FileTransferHandler::ExecuteRequestedCommand(Header header)
	{
		std::string szHeaderData = header.headerData;
		std::istringstream ssHeader(szHeaderData);
		SOCKET socket = sessionData_.socket;
		std::unique_ptr<ICommand> command;

		if (Utilities::CheckRequestFormat::IsValidRequestPattern(
			Utilities::CheckRequestFormat::ftpPattern_SetupCall,
			szHeaderData)) {
			command = CommandManager::CommandTable::Instance().CommandLookup(SETUP_CALL);
		}
		else if (Utilities::CheckRequestFormat::IsValidRequestPattern(
			Utilities::CheckRequestFormat::ftpPattern_FileAcquire,
			szHeaderData)) {
			command = CommandManager::CommandTable::Instance().CommandLookup(FILE_ACQUIRE);
		}
		else if (Utilities::CheckRequestFormat::IsValidRequestPattern(
			Utilities::CheckRequestFormat::ftpPattern_FileDispatch,
			szHeaderData)) {
			command = CommandManager::CommandTable::Instance().CommandLookup(FILE_DISPATCH);
		}
		else
		{
			Logger::LOG[Logger::Level::Critical] << "Invalid command pattern supplied" << Logger::endl;
			return;
		}

		if (command) {
			command->Execute(ssHeader, socket);
		}

	}
}