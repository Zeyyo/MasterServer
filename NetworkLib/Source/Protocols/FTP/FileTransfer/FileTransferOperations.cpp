#include "NEtw_pch.h"

#include "Protocols/FTP/config.h"
#include "Types/File.h"

#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/FileOperations/FileOperations.h"
#include "Utilities/Packing/Packing.h"
#include "Utilities/NameMangling/NameMangling.h"
#include "utilities/ZeroBuffer/ZeroBuffer.h"

#include "Events/Exceptions/FileTransferHandlerExceptions.h"
#include "Events/Exceptions/FileOperationExceptions.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "FileTransferOperations.h"
#include "Events/Logger/OstreamLogger.h"

#include "Crypto/CryptoService.h"

namespace FileTransferOperations
{
	bool ReceiveFileSecure(SOCKET socket, Base64FileDataSecure& kFileData)
	{
		kFileData.pPackagedFileBinary->binary = new char[kFileData.nFileSize];
		Utilities::Memory::ZeroBufferMemory(kFileData.pPackagedFileBinary->binary, kFileData.nFileSize);
		Utilities::NameMangling::SuffixMangle(kFileData.szFileName);

		bool success = Utilities::SocketOperations::ReceiveFileFromPeer(
			socket,
			kFileData.pPackagedFileBinary->binary,
			kFileData.nFileSize);
		if (!success)
			return false;
		
		success = Utilities::Packing::UnpackFileSecure(
			kFileData.pFileBinary->binary,
			kFileData.nFileSize,
			kFileData.pPackagedFileBinary->binary,
			kFileData.szKey,
			kFileData.szIv);
		if (!success)
			return false;

		success = Utilities::FileOperations::SaveFileSecure(
			kFileData, 
			DEFAULT_RECEIVE_LOCATION);
		if (!success)
			return false;
		return true;
	}

	bool ReceiveFile(SOCKET socket, Base64FileData& kFileData)
	{
		kFileData.pPackagedFileBinary->binary = new char[kFileData.nFileSize];
		Utilities::Memory::ZeroBufferMemory(kFileData.pPackagedFileBinary->binary, kFileData.nFileSize);
		Utilities::NameMangling::SuffixMangle(kFileData.szFileName);

		bool success = Utilities::SocketOperations::ReceiveFileFromPeer(
			socket,
			kFileData.pPackagedFileBinary->binary,
			kFileData.nFileSize);
		if (!success)
			return false;

		success = Utilities::Packing::UnpackFile(
			kFileData.pFileBinary->binary,
			kFileData.nFileSize,
			kFileData.pPackagedFileBinary->binary,
			kFileData.szKey,
			kFileData.szIv);
		if (!success)
			return false;

		success = Utilities::FileOperations::SaveFile(
			kFileData,
			DEFAULT_RECEIVE_LOCATION);
		if (!success)
			return false;

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
		char* prawSendFileBuffer = fileData.pFileBinary->binary;

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