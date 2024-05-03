#include "NEtw_pch.h"

#include <integer.h>
#include <pubkey.h>
#include "cryptlib.h"
#include <rsa.h>
#include "hex.h"
#include <io.h>
#include <osrng.h>

#include "pem.h"

#include "config.h"
#include "Events/Exceptions/CryptoOperationException.h"

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
        return szEncryptedData.c_str();
    }

    const char* CryptoService::RSADecryptHeader(const char* pksBuffer)
    {
        AutoSeededRandomPool prng;
        auto privateKey = loadKey<RSA::PrivateKey>(DEFAULT_RSA_PRIVATE_KEY_LOC);
        std::string szDecryptedData;

        try
        {
            RSAES_OAEP_SHA_Decryptor d(privateKey);
            StringSource(pksBuffer, true,
                new PK_DecryptorFilter(prng, d,
                    new StringSink(szDecryptedData)));
        }
        catch (Exception& e)
        {
            std::string message = e.what();
            throw Exceptions::CryptoOperationException::HeaderDecryptionException(message);
        }
        return szDecryptedData.c_str();
    }
}

bool Crypto::CryptoService::operator==(const CryptoService& other) const
{
    return false;
}
