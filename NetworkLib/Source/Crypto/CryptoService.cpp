#include "NEtw_pch.h"

#include <integer.h>
#include "cryptlib.h"
#include <pubkey.h>
#include <modes.h>

#include <rsa.h>
#include <aes.h>

#include <hex.h>
#include "base64.h"

#include <osrng.h>
#include "pem.h"
#include <io.h>

#include "config.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Utilities/Crypto/Base64EncDec.h"
#include "Utilities/Crypto/HexEncDec.h"
#include "CryptoService.h"

namespace CryptoService
{
    namespace CryptoProvider = CryptoPP;
    using CryptoProvider::AutoSeededRandomPool;
    using CryptoProvider::RSA;
    using CryptoProvider::AES;
    using CryptoProvider::RSAES_OAEP_SHA_Encryptor;
    using CryptoProvider::RSAES_OAEP_SHA_Decryptor;
    using CryptoProvider::PK_EncryptorFilter;
    using CryptoProvider::PK_DecryptorFilter;
    using CryptoProvider::StringSource;
    using CryptoProvider::StringSink;
    using CryptoProvider::Exception;
    using CryptoProvider::SecByteBlock;
    using CryptoProvider::CBC_Mode;
    using CryptoProvider::StreamTransformationFilter;
    using CryptoProvider::ArraySink;
    using CryptoProvider::byte;
    

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

    std::string CryptoService::RSADecryptHeaderData(std::string pksBuffer)
    {
        auto privateKey = loadKey<RSA::PrivateKey>(DEFAULT_RSA_PRIVATE_KEY_LOC);
        AutoSeededRandomPool prng;
        std::string recovered;

        try
        {
            RSAES_OAEP_SHA_Decryptor d(privateKey);
            StringSource(pksBuffer, true,
                new PK_DecryptorFilter(prng, d,
                    new StringSink(recovered)));
        }
        catch (const Exception& e)
        {
            std::string message = e.what();
            throw Exceptions::CryptoOperationException::HeaderDecryptionException(message);
        }
        return recovered;
    }

    const char* CryptoService::DSAEncryptData(const char* pksDataBuffer)
    {
        // TODO
        return "sdf";
    }

    std::string CryptoService::DSADecryptData(const char* pksDataBuffer, std::string szKey, std::string szIv)
    {
        SecByteBlock key = Utilities::Crypto::StringToSecByteBlockDecode(szKey);
        SecByteBlock iv = Utilities::Crypto::StringToSecByteBlockDecode(szIv);

        std::string recovered;
        std::string szDecodedBuffer = Utilities::Crypto::Base64Decode(pksDataBuffer);
        try
        {
            CBC_Mode< AES >::Decryption d;
            d.SetKeyWithIV(key.data(), key.size(), iv);

            StringSource s(szDecodedBuffer, true,
                new StreamTransformationFilter(d,
                    new StringSink(recovered)
                )
            );
        }
        catch (const Exception& e)
        {
            std::string message = e.what();
            throw Exceptions::CryptoOperationException::DataDecryptionException(message);
        }
        return recovered;
    }

    char* CryptoService::DSADecryptFileData(const char* pkDataBuffer, size_t fileSize, std::string szKey, std::string szIv) 
    {
        SecByteBlock key = Utilities::Crypto::StringToSecByteBlockDecode(szKey);
        SecByteBlock iv = Utilities::Crypto::StringToSecByteBlockDecode(szIv);

        char* recovered = new char[fileSize];

        try {
            CBC_Mode<AES>::Decryption cbcDecryption;
            cbcDecryption.SetKeyWithIV(key, key.size(), iv);

            StreamTransformationFilter decryptor(cbcDecryption, new ArraySink((byte*)recovered, fileSize));
            decryptor.Put((const byte*)pkDataBuffer, fileSize);
            decryptor.MessageEnd();
        }
        catch (const Exception& e) {
            std::string message = e.what();
            delete[] pkDataBuffer;
            throw Exceptions::CryptoOperationException::DataDecryptionException(message);
        }

        delete[] pkDataBuffer;
        return recovered;
    }

    bool CryptoService::operator==(const CryptoService& other) const
    {
        return false;
    }
}