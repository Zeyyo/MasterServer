#pragma once
#include "pch.h"

namespace Exceptions::NetworkOperationExceptions
{
    class SessionInitializationException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        SessionInitializationException(const std::string& error) : szErrorMessage("Session initialization failed: " + error) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class SessionHandlingException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        SessionHandlingException(const std::string& error) : szErrorMessage("Session handling error: " + error) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

}