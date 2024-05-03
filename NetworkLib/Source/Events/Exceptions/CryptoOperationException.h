#pragma once

#include <string>
#include <exception>

namespace Exceptions::CryptoOperationException
{
    class HeaderEncryptionException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        HeaderEncryptionException(const std::string& message) : szErrorMessage("Failed to encrypt header: " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class HeaderDecryptionException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        HeaderDecryptionException(const std::string& message) : szErrorMessage("Failed to decrypt header: " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}