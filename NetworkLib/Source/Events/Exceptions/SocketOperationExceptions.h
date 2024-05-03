#pragma once

#include <string>
#include <exception>

namespace Exceptions::SocketOperationExceptions
{
    class SocketCreationException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        SocketCreationException(const DWORD& error) : szErrorMessage("Failed to create socket: " + std::to_string(error)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class BindException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        BindException(const DWORD& error) : szErrorMessage("Failed to bind socket: " + error) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class AcceptException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        AcceptException(const DWORD& error) : szErrorMessage("Failed to accept connection: " + error) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class ReceiveDataException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ReceiveDataException(const DWORD& address) : szErrorMessage("Failed to receive data from peer: " + address) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class ReceiveTimeOutException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ReceiveTimeOutException(const std::string& details) : szErrorMessage("Receive operation timed out: " + details) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class SendDataException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        SendDataException(const DWORD& address) : szErrorMessage("Failed to send data to peer: " + address) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class SendTimeOutException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        SendTimeOutException(const std::string& details) : szErrorMessage("Send operation timed out: " + details) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}
