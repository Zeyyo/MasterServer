#pragma once
#include <files.h>

namespace CryptoService
{
    class CryptoService
    {
    public:
        const char* RSAEncryptHeader(const char* pksBuffer);
        std::string RSADecryptHeaderData(std::string pksBuffer);

        const char* DSAEncryptData(const char* pksDataBuffer);
        std::string DSADecryptData(const char* pksDataBuffer, std::string szKey, std::string szIv);
        char* DSADecryptFileData(const char* pksDataBuffer, size_t fileSize, std::string szKey, std::string szIv);

    private:
        template <typename Key>
        const Key loadKey(const std::string& filename)
        {
            Key key;
            CryptoPP::ByteQueue queue;
            CryptoPP::FileSource file(filename.c_str(), true);

            file.TransferTo(queue);
            queue.MessageEnd();

            key.Load(queue);
            return key;
        }
    public:
        bool operator==(const CryptoService& other) const;
    };
}