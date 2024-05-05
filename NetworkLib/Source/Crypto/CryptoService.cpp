#include "NEtw_pch.h"

#include <integer.h>
#include <pubkey.h>
#include "cryptlib.h"
#include <rsa.h>
#include "hex.h"
#include "base64.h"
#include <io.h>
#include <osrng.h>

#include "pem.h"

#include "config.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Utilities/Crypto/Base64EncDec.h"
#include "CryptoService.h"

namespace Crypto
{
    namespace CryptoProvider = CryptoPP;
    using CryptoProvider::AutoSeededRandomPool;
    using CryptoProvider::RSA;
    using CryptoProvider::RSAES_OAEP_SHA_Encryptor;
    using CryptoProvider::RSAES_OAEP_SHA_Decryptor;
    using CryptoProvider::PK_EncryptorFilter;
    using CryptoProvider::PK_DecryptorFilter;
    using CryptoProvider::StringSource;
    using CryptoProvider::StringSink;
    using CryptoProvider::Exception;


    const char* CryptoService::RSAEncryptHeader(const char* pksBuffer)
    {
        AutoSeededRandomPool prng;
        auto publicKey = loadKey<RSA::PublicKey>(DEFAULT_RSA_PUBLIC_KEY_LOC);
        std::string szEncryptedData;

        try
        {
            RSAES_OAEP_SHA_Encryptor e(publicKey);
            StringSource(pksBuffer, true, 
                new PK_EncryptorFilter(prng, e, 
                    new StringSink(szEncryptedData)));
        }
        catch (Exception& e)
        {
            std::string message = e.what();
            throw Exceptions::CryptoOperationException::HeaderEncryptionException(message);
        }
        //char* buffer = new char[szDecryptedData.length()];
        //memcpy_s(buffer, szDecryptedData.length(), szDecryptedData.c_str(), szDecryptedData.length());
        return szEncryptedData.c_str();
    }

    

    std::string CryptoService::RSADecryptHeader(const char* pksBuffer)
    {
        auto privateKey = loadKey<RSA::PrivateKey>(DEFAULT_RSA_PRIVATE_KEY_LOC);
        AutoSeededRandomPool prng;
        std::string szDecrypted = "";

        std::string szDecodedBuffer = Utilities::Crypto::Base64Decode(pksBuffer);
        try
        {
            RSAES_OAEP_SHA_Decryptor d(privateKey);
            StringSource(szDecodedBuffer, true,
                new PK_DecryptorFilter(prng, d,
                    new StringSink(szDecrypted)));
        }
        catch (Exception& e)
        {
            std::string message = e.what();
            throw Exceptions::CryptoOperationException::HeaderDecryptionException(message);
        }
        return szDecrypted;
    }
}

bool Crypto::CryptoService::operator==(const CryptoService& other) const
{
    return false;
}
