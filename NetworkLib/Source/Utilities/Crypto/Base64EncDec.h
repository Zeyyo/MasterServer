#pragma once

namespace Utilities::Crypto
{
    std::string Base64Encode(std::string szBuffer);
    std::string Base64Decode(const char* pkBase64Buffer);
    char* Base64DecodeFileData(const char* pkBase64Buffer);
}