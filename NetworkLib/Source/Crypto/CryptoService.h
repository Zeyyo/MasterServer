#pragma once
#include <files.h>

namespace Crypto
{
    class CryptoService
    {
    public:
        const char* RSAEncryptHeader(const char* pksBuffer);
        std::string RSADecryptHeader(const char* pksBuffer);

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