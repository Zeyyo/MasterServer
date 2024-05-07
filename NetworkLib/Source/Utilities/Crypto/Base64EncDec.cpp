#include "NEtw_pch.h"

#include "cryptlib.h"
#include <base64.h>
#include "Utilities/ZeroBuffer/ZeroBuffer.h"

#include "Base64EncDec.h"

namespace Utilities::Crypto
{
    using CryptoPP::Base64Decoder;
    using CryptoPP::Base64Encoder;
    using CryptoPP::StringSource;
    using CryptoPP::StringSink;
    using CryptoPP::ArraySink;
    using CryptoPP::byte;

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

    char* Base64DecodeFileData(const char* pkBase64Buffer)
    {
        size_t inputSize = strlen(pkBase64Buffer);
        char* pDecodedBuffer = new char[inputSize];
        Utilities::Memory::ZeroBufferMemory(pDecodedBuffer, inputSize);

        Base64Decoder decoder(new ArraySink((byte*)pDecodedBuffer, inputSize));
        decoder.Put((const byte*)pkBase64Buffer, inputSize);
        decoder.MessageEnd();
        return pDecodedBuffer;
    }
}
