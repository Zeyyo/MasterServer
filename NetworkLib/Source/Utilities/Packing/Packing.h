#pragma once
#include "Types/Header.h"

namespace Utilities::Packing
{
	bool UnpackFile(
		char* binary,
		size_t fileSize,
		const char* pkBase64Buffer,
		std::string szKey,
		std::string szIv);

	bool UnpackFileSecure(
		char*& binary,
		size_t fileSize,
		const char* pkBase64Buffer,
		std::string szKey,
		std::string szIv);

	bool UnpackHeader(const char* pkBase64Buffer, Header& header);
	bool UnpackHeaderSecure(const char* pkBase64Buffer, Header& heade);

}
