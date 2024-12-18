#include "NEtw_pch.h"

#include <fstream>
#include <filesystem>
#include <string>

#include "Helpers/OperationHelper/OperationHelper.h"
#include "Events/Logger/OstreamLogger.h"
#include "Types/File.h"
#include "Events/Exceptions/FileOperationExceptions.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Crypto/CryptoService.h"
#include "Utilities/Crypto/Base64EncDec.h"

#include "FileOperations.h"

namespace Utilities::FileOperations
{
	void CreatePeerDirecory(std::string& szPath)
	{
		std::filesystem::create_directory(szPath);
	}

	void CreateFileForWriting(std::ofstream& outFile, const std::string& kszFilePath)
	{
		outFile.open(kszFilePath, std::ios::binary | std::ios::out);
		if (!outFile.is_open())
			throw Exceptions::FileOperationExceptions::FileCreateException(kszFilePath);
	}

	void OpenFileForReading(std::ifstream& outFile, const std::string& kszFilePath)
	{
		outFile.open(kszFilePath, std::ios::binary);
		if (!outFile.is_open())
			throw Exceptions::FileOperationExceptions::FileCreateException(kszFilePath);
	}

	void StoreFile(
		const std::string& kszName, 
		const std::string& kszExtension, 
		const char* pkrawDataBuffer,
		size_t length,
		const std::string& kszSaveStorageLocation)
	{
		std::ostringstream ssFilePath;
		ssFilePath << kszSaveStorageLocation << "/" << kszName << "." << kszExtension;
		std::string szFilePath = ssFilePath.str();

		if (std::filesystem::exists(szFilePath))
			throw Exceptions::FileOperationExceptions::FileAlreadyExistsException(szFilePath);

		std::ofstream outFile;
		bool bSuccess = Helpers::OperationHelper<Exceptions::FileOperationExceptions::FileCreateException>::
			AttemptOperation(3, 300, [&]()
				{ CreateFileForWriting(outFile, szFilePath); } ,
				[](Exceptions::FileOperationExceptions::FileCreateException) {});
		if (bSuccess == false)
			throw Exceptions::FileOperationExceptions::FileCreateTimeOutException("Exception thrown at StoreFile()");

		outFile.write(pkrawDataBuffer, length);

		outFile.close();
		Logger::LOG[Logger::Level::Info] << "File \"" << kszName << "\" stored!" << Logger::endl;
	}

	FileData LoadFile(
		const std::string& kszFileName, 
		const std::string& kszLoadStorageLocation)
	{
		const std::string kszFileExtension = ".txt";
		std::ostringstream ssFilePath;
		ssFilePath << kszLoadStorageLocation << "/" << kszFileName << "." << kszFileExtension;
		const std::string kszFilePath = ssFilePath.str();

		if (!std::filesystem::exists(kszFilePath))
			throw Exceptions::FileOperationExceptions::FileNotFoundException(kszFilePath);

		std::ifstream inFile;
		bool bSuccess = Helpers::OperationHelper<Exceptions::FileOperationExceptions::FileLoadException>::
			AttemptOperation(3, 300, [&]()
				{ OpenFileForReading(inFile, kszFilePath); },
				[](Exceptions::FileOperationExceptions::FileLoadException) {});

		if (bSuccess == false)
			throw Exceptions::FileOperationExceptions::FileLoadTimeoutException("Exception thrown at LoadFile()");

		inFile.seekg(0, std::ios::end);
		const size_t knFileSize = inFile.tellg();
		char* prawLoadFileBuffer = new char[knFileSize];
		inFile.read(prawLoadFileBuffer, knFileSize);

		FileData fileData(kszFileName, knFileSize, kszFileExtension);
		fileData.pFileBinary->binary = prawLoadFileBuffer;
		fileData.pFileBinary->length = knFileSize;

		Logger::LOG[Logger::Level::Info] << "File \"" << kszFileName << "\" loaded!" << Logger::endl;
		return fileData;
	}

	bool SaveFile(Base64FileData& kFileData, std::string location)
	{
		try
		{
			Utilities::FileOperations::StoreFile(
				kFileData.szName,
				/*kFileData.szExtension*/ "jpg",
				kFileData.pBinary->binary,
				kFileData.pBinary->length,
				location);
		}
		catch (Exceptions::FileOperationExceptions::FileAlreadyExistsException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << Logger::endl;
			return false;
		}
		catch (Exceptions::FileOperationExceptions::FileCreateTimeOutException& e)
		{
			// TODO temporary cache the data
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << Logger::endl;
			return false;
		}
	}

	bool SaveFileSecure(Base64FileDataSecure& kFileData, std::string location)
	{
		try
		{
			Utilities::FileOperations::StoreFile(
				kFileData.szName,
				kFileData.szExtension,
				kFileData.pBinary->binary,
				kFileData.pBinary->length,
				location);
		}
		catch (Exceptions::FileOperationExceptions::FileAlreadyExistsException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << Logger::endl;
			return false;
		}
		catch (Exceptions::FileOperationExceptions::FileCreateTimeOutException& e)
		{
			// TODO temporary cache the data
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << Logger::endl;
			return false;
		}
	}

	bool SaveFileSecure(Base64FileDataSecure& kFileData, std::string location, std::string& id)
	{
		std::ostringstream ssPath;
		ssPath << location << "/" << id;
		std::string szPath = ssPath.str();

		if (!std::filesystem::exists(szPath))
			CreatePeerDirecory(szPath);

		try
		{
			Utilities::FileOperations::StoreFile(
				kFileData.szName,
				kFileData.szExtension,
				kFileData.pBinary->binary,
				kFileData.pBinary->length,
				szPath);
		}
		catch (Exceptions::FileOperationExceptions::FileAlreadyExistsException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << Logger::endl;
			return false;
		}
		catch (Exceptions::FileOperationExceptions::FileCreateTimeOutException& e)
		{
			// TODO temporary cache the data
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << Logger::endl;
			return false;
		}
	}
}