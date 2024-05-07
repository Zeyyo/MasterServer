#include "NEtw_pch.h"

#include "cryptlib.h"
#include <base64.h>

#include "Base64EncDec.h"

namespace Utilities::Crypto
{
    using CryptoPP::Base64Decoder;
    using CryptoPP::Base64Encoder;
    using CryptoPP::StringSource;
    using CryptoPP::StringSink;

    std::string Base64Encode(std::string szBuffer)
    {
        std::string szEncodedBuffer;
        StringSource(szBuffer, true, new Base64Encoder(new StringSink(szEncodedBuffer))
        );
        return szEncodedBuffer;
    }

    std::string Base64Decode(const char* pkBase64Buffer)
    {
        std::string szDecodedBuffer;
        StringSource(pkBase64Buffer, true, new Base64Decoder(new StringSink(szDecodedBuffer))
        );
        return szDecodedBuffer;
    }
}
