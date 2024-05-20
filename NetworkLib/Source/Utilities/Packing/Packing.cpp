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
	WORD UnpackFile(
		char** binary, 
		size_t& binarySize,
		const char* pkBase64Buffer,
		size_t pkBase64Len,
		std::string szKey,
		std::string szIv)
	{
		try
		{
			*binary = Utilities::Crypto::Base64DecodeFileData(pkBase64Buffer, pkBase64Len);
		}
		catch (Exceptions::CryptoOperationException::DataDecryptionException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at UnpackFile()." << Logger::endl;
			return -1;
		}
		return 0;
	}

	WORD UnpackFileSecure(
		char** binary,
		size_t& binarySize,
		const char* pkPackedBuffer,
		size_t pkPackedLen,
		std::string szKey,
		std::string szIv)
	{
		try
		{
			char* pDecodedBuffer = Utilities::Crypto::Base64DecodeFileData(pkPackedBuffer, pkPackedLen);
			*binary = CryptoService::CryptoService().AESDecryptFileData(
				pDecodedBuffer,
				pkPackedLen,
				binarySize,
				szKey,
				szIv);
		}
		catch (Exceptions::CryptoOperationException::DataDecryptionException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at UnpackFile()." << Logger::endl;
			return -1;
		}
		return 0;
	}

	WORD UnpackHeader(const char* pkBase64Buffer, Header& header)
	{
		header.headerData = Utilities::Crypto::Base64Decode(pkBase64Buffer);
		header.headerSize = header.headerData.length();

		// TODO error handling
		return 0;
	}

	WORD UnpackHeaderSecure(const char* pkBase64Buffer, Header& header)
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
			return -1;
		}
		header.headerSize = header.headerData.length();
		return 0;
	}

}