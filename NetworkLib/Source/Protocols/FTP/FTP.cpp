#include "NEtw_pch.h"

#include "config.h"
#include <map>
#include <sstream>
#include "Types/File.h"

#include "Events/Logger/OstreamLogger.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Events/Exceptions/NetworkOperationExceptions.h"
#include "Events/Exceptions/ConnectionManagerExceptions.h"

#include "Server/SessionHandling/Session/Session.h"

#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/CheckRequestFormat/CheckRequestFormat.h"
#include "Utilities/Packing/Packing.h"

#include "Crypto/CryptoService.h"

#include "FTP.h"

void ftpMod(NetworkLibrary::SessionData& sessionData)
{
	ProtocolHandlers::FTP::FileTransferHandler fileTransferHandler(sessionData);
	fileTransferHandler.ProcessRequest();
}

namespace ProtocolHandlers::FTP
{
	void FileTransferHandler::ProcessRequest()
	{
		Header header;
		try
		{
			header = AcceptHeader();
		}
		catch (const Exceptions::NetworkOperationExceptions::FailedReceivingHeaderException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Critical] << szErrorMessage << Logger::endl;
			return;
		}
		catch (const Exceptions::NetworkOperationExceptions::FailedUnpackingHeaderException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Critical] << szErrorMessage << Logger::endl;
			return;
		}
		
		try
		{
			ExecuteCommand(header);
		}
		catch (const Exceptions::CommandManagerExceptions::InvalidCommandPattern& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Critical] << szErrorMessage << Logger::endl;
			return;
		}
		catch (const Exceptions::CommandManagerExceptions::CommandKeyMismatch& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Critical] << szErrorMessage << Logger::endl;
			return;
		}
	}

	Header FileTransferHandler::AcceptHeader()
	{
		Header header;
		WORD wRes = Utilities::SocketOperations::ReceiveHeaderFromPeer(sessionData_.socket,
			sInitRequestHeaderBuffer_,
			DEFAULT_HEADER_BASE64_HEADER_LEN);
		if (wRes != 0)
			throw Exceptions::NetworkOperationExceptions::FailedReceivingHeaderException("Exception thrown at ReceiveHeaderFromPeer()");

		wRes = Utilities::Packing::UnpackHeaderSecure(sInitRequestHeaderBuffer_, header);
		if (wRes != 0)
			throw Exceptions::NetworkOperationExceptions::FailedUnpackingHeaderException("Exception thrown at UnpackHeaderSecure()");

		return header;
	}

	void FileTransferHandler::ExecuteCommand(Header header)
	{
		std::string szHeaderData = header.headerData;
		std::istringstream ssHeader(szHeaderData);
		SOCKET socket = sessionData_.socket;
		std::unique_ptr<CommandManager::ICommand> command;

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
			throw Exceptions::CommandManagerExceptions::InvalidCommandPattern("Exception thrown at ExecuteCommand()");
			return;
		}

		if (command == nullptr) 
		{
			throw Exceptions::CommandManagerExceptions::CommandKeyMismatch("Exception thrown at CommandLookup()");
			return; 
		}
		command->Execute(ssHeader, socket, sessionData_.szIpAdress);
		return;
	}
}