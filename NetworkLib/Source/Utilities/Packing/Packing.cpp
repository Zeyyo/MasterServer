#include "NEtw_pch.h"

#include <string>

#include "Events/Logger/OstreamLogger.h"
#include "Types/File.h"
#include "Types/Header.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Crypto/CryptoService.h"
#include "Utilities/Crypto/Base64EncDec.h"

#include "Packing.h"

namespace Utilities::Packing
{
	bool UnpackFile(
		char* binary, 
		size_t fileSize,
		const char* pkBase64Buffer,
		std::string szKey,
		std::string szIv)
	{
		try
		{
			binary = Utilities::Crypto::Base64DecodeFileData(pkBase64Buffer, fileSize);
		}
		catch (Exceptions::CryptoOperationException::DataDecryptionException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at UnpackFile()." << Logger::endl;
			return false;
		}
	}

	bool UnpackFileSecure(
		char*& binary,
		size_t fileSize,
		const char* pkBase64Buffer,
		std::string szKey,
		std::string szIv)
	{
		try
		{
			char* pDecodedBuffer = Utilities::Crypto::Base64DecodeFileData(pkBase64Buffer, fileSize);
			binary = CryptoService::CryptoService().DSADecryptFileData(
				pDecodedBuffer,
				fileSize,
				szKey,
				szIv);
		}
		catch (Exceptions::CryptoOperationException::DataDecryptionException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at UnpackFile()." << Logger::endl;
			return false;
		}
	}

	bool UnpackHeader(const char* pkBase64Buffer, Header& header)
	{
		header.headerData = Utilities::Crypto::Base64Decode(pkBase64Buffer);
		header.headerSize = header.headerData.length();

		// TODO error handling
		return 1;

	}

	bool UnpackHeaderSecure(const char* pkBase64Buffer, Header& header)
	{
		std::string kszHeader;
		try
		{
			std::string sHeader = Utilities::Crypto::Base64DecodeHeaderData(pkBase64Buffer);
			header.headerData = CryptoService::CryptoService().RSADecryptHeaderData(sHeader);
		}
		catch (Exceptions::CryptoOperationException::HeaderDecryptionException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at RSADecryptHeaderData()." << Logger::endl;
			// TODO failed to decrypt data -> Close connection
			return 0;
		}
		header.headerSize = header.headerData.length();
		return 1;
	}

}