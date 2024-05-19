#pragma once

namespace Utilities::Crypto
{
    std::string Base64Encode(std::string szBuffer);
    std::string Base64Decode(const char* pkBase64Buffer);
    std::string Base64EncodeHeaderData(std::string szBuffer);
    std::string Base64DecodeHeaderData(const char* pkBase64Buffer);

    size_t B64EncodedSize(size_t inlen);
	size_t B64DecodedSize(size_t base64len);

    char* Base64DecodeFileData(const char* pkBase64Buffer, size_t& len);
}