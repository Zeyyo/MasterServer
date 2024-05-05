#pragma once

namespace Utilities::Crypto
{
    std::string Base64Encode(const char* pkBuffer);
    std::string Base64Decode(const char* pkBase64Buffer);
}