#include "pch.h"
#include "FileTransferOperations.h"

namespace FileTransferOperations
{
	bool ReceiveFile(SOCKET socket, const FileData& kFileData)
	{
		char* prawReceiveFileBuffer = new char[kFileData.nFileSize];
		std::string szFileName = kFileData.szFileName;
		size_t nFileSize = kFileData.nFileSize;
		std::string szFileExtension = kFileData.szFileExtension;

		try
		{
			Utilitis::SocketOperations::Receive(socket, prawReceiveFileBuffer, nFileSize);
			Utilitis::FileOperations::StoreFile(szFileName, szFileExtension, prawReceiveFileBuffer, DEFAULT_RECEIVE_LOCATION);
		}
		catch (Exceptions::SocketOperationExceptions::ReceiveTimeOutException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReceiveFile()." << Logger::endl;
			return false;
		}
		catch (Exceptions::FileOperationExceptions::FileAlreadyExistsException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReceiveFile()." << Logger::endl;
			return false;
		}
		catch (Exceptions::FileOperationExceptions::FileCreateTimeOutException& e)
		{
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
			fileData = Utilitis::FileOperations::LoadFile(szFileName, DEFAULT_LOAD_LOCATION);
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
			Utilitis::SocketOperations::Send(socket, prawSendFileBuffer, nFileSize);
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
