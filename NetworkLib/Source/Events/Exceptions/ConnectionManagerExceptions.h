#pragma once
#include "pch.h"

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
}
