#pragma once

#include <string>
#include <exception>

namespace Exceptions::ConnectionManagerExceptions
{
    class ConnectionManagerInitializationException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ConnectionManagerInitializationException(const std::string& errorDetails) :
            szErrorMessage("Connection Manager initialization failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class AbortConnection : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        AbortConnection(const std::string& message) : szErrorMessage("Connection aborted: " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class GetPeerInfoException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        GetPeerInfoException(const DWORD dwRetval) :
            szErrorMessage("An attempt at getting host-information from peer failed with code: " + std::to_string(dwRetval)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class GetPeerAddrException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        GetPeerAddrException(const DWORD dwRetval) :
            szErrorMessage("An attempt at getting address-information from peer failed with code: " + std::to_string(dwRetval)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}
