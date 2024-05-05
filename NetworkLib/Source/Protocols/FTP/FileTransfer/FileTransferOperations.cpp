#include "NEtw_pch.h"

#include "Protocols/FTP/config.h"
#include "Types/File.h"
#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/FileOperations/FileOperations.h"
#include "Events/Exceptions/FileTransferHandlerExceptions.h"
#include "Events/Exceptions/FileOperationExceptions.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "FileTransferOperations.h"
#include "Events/Logger/OstreamLogger.h"
#include "Utilities/NameMangling/NameMangling.h"
#include "utilities/ZeroBuffer/ZeroBuffer.h"

namespace FileTransferOperations
{
	bool ReceiveFile(SOCKET socket, const FileData& kFileData)
	{
		size_t nFileSize = kFileData.nFileSize;
		char* prawReceiveFileBuffer = new char[nFileSize];
		Utilities::Memory::ZeroBufferMemory(prawReceiveFileBuffer, nFileSize);

		std::string szFileExtension = kFileData.szFileExtension;
		std::string szFileNameNoMangle = kFileData.szFileName;
		std::string szFileName = Utilities::NameMangling::SuffixMangle(szFileNameNoMangle);

		try
		{
			Utilities::SocketOperations::Receive(socket, prawReceiveFileBuffer, nFileSize);
		}
		catch (Exceptions::SocketOperationExceptions::ReceiveTimeOutException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReceiveFile()." << Logger::endl;
			return false;
		}
		catch (Exceptions::SocketOperationExceptions::SocketBufferEmptyException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReceiveFile()." << Logger::endl;
			// TODO: Close connection
		}

		try 
		{
			Utilities::FileOperations::StoreFile(szFileName, "txt", prawReceiveFileBuffer, DEFAULT_RECEIVE_LOCATION);
		}
		catch (Exceptions::FileOperationExceptions::FileAlreadyExistsException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReceiveFile()." << Logger::endl;
			return false;
		}
		catch (Exceptions::FileOperationExceptions::FileCreateTimeOutException& e)
		{
			// TODO temporary cache the data
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReceiveFile()." << Logger::endl;
			return false;
		}
		return true;
	}

	bool TransmitFile(SOCKET socket, std::string& szFileName)
	{
		FileData fileData;
		try
		{
			fileData = Utilities::FileOperations::LoadFile(szFileName, DEFAULT_LOAD_LOCATION);
		}
		catch (Exceptions::FileOperationExceptions::FileNotFoundException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at TransmitFile()." << Logger::endl;
			return false;
		}
		catch (Exceptions::FileOperationExceptions::FileLoadTimeoutException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at TransmitFile()." << Logger::endl;
			return false;

		}
		size_t nFileSize = fileData.nFileSize;
		char* prawSendFileBuffer = fileData.prawBinaryFileData;

		try 
		{
			Utilities::SocketOperations::Send(socket, prawSendFileBuffer, nFileSize);
		}
		catch (Exceptions::SocketOperationExceptions::SendTimeOutException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at TransmitFile()." << Logger::endl;
			return false;

		}
		return true;
	}
}