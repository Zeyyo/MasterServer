#pragma once

#include <string>
#include <exception>

namespace Exceptions::ServerCoreExceptions
{
    class CoreInitializationException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        CoreInitializationException(const DWORD& error) : szErrorMessage("Core initialization failed: " + error) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}
