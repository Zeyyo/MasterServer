#pragma once
#include "Types/Header.h"

namespace Utilities::Packing
{
	WORD UnpackFile(
		char** binary,
		size_t& binarySize,
		const char* pkBase64Buffer,
		size_t pkBase64Len,
		std::string szKey,
		std::string szIv);

	WORD UnpackFileSecure(
		char** binary,
		size_t& binarySize,
		const char* pkBase64Buffer,
		size_t pkBase64Len,
		std::string szKey,
		std::string szIv);

	WORD UnpackHeader(const char* pkBase64Buffer, Header& header);
	WORD UnpackHeaderSecure(const char* pkBase64Buffer, Header& heade);

}
