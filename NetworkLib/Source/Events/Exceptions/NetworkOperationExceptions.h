#pragma once
#include "NEtw_pch.h"

namespace Exceptions::NetworkOperationExceptions
{
    class FailedToReceiveHeaderPrefixException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FailedToReceiveHeaderPrefixException(const std::string& details) : szErrorMessage("Failed to receive header prefix: " + details) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class InvalidHeaderPrefixException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        InvalidHeaderPrefixException(const std::string& details) : szErrorMessage("Invalid header prefix suplied: " + details) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}
