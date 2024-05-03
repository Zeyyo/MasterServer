#pragma once

#include <string>
#include <exception>

namespace Exceptions::FileTransferHandlerExceptions
{
    class InitRequestHandlingException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        InitRequestHandlingException(const std::string& errorDetails) :
            szErrorMessage("Initialization of request handler failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class ProcessHeaderException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ProcessHeaderException(const std::string& errorDetails) :
            szErrorMessage("Header processing failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class FileAcquireException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileAcquireException(const std::string& errorDetails) :
            szErrorMessage("File acquisition failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class FileDispatchException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileDispatchException(const std::string& errorDetails) :
            szErrorMessage("File dispatch failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

}