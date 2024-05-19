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

    std::string Base64EncodeHeaderData(std::string szBuffer)
    {
        std::string szDecodedBuffer;
        StringSource(szBuffer, true, new Base64Decoder(new StringSink(szDecodedBuffer))
        );
        return szDecodedBuffer;
    }

    std::string Base64DecodeHeaderData(const char* pkBase64Buffer)
    {
        std::string szDecodedBuffer;
        StringSource(pkBase64Buffer, true, new Base64Decoder(new StringSink(szDecodedBuffer))
        );
        return szDecodedBuffer;
    }

    char* Base64DecodeFileData(const char* pkBase64Buffer, size_t& len)
    {
        size_t dataLen = len;
        len = Utilities::Crypto::B64DecodedSize(len);
        char* pDecodedBuffer = new char[len];
        Utilities::Memory::ZeroBufferMemory(pDecodedBuffer, len);

        Base64Decoder decoder(new ArraySink((byte*)pDecodedBuffer, len));
        decoder.Put((const byte*)pkBase64Buffer, dataLen);
        decoder.MessageEnd();
        return pDecodedBuffer;
    }

    size_t B64EncodedSize(size_t inlen)
    {
        size_t ret;

        ret = inlen;
        if (inlen % 3 != 0)
            ret += 3 - (inlen % 3);
        ret /= 3;
        ret *= 4;

        return ret;
    }

    size_t B64DecodedSize(size_t inlen) 
    {
        size_t ret = (inlen * 3) / 4;

        if (ret % 4 == 0) {
        }
        else if (ret % 4 == 1) {
            ret -= 1;
        }
        else if (ret % 4 == 2) {
            ret -= 2;
        }
        else if (ret % 4 == 3) {
            ret -= 3;
        }

        return ret;
    }
}
