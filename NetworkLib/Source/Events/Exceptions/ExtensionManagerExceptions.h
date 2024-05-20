#pragma once
#include <string>
#include <exception>

namespace Exceptions::ExtensionManagerExceptions
{
    class ExtensionKeyMismatch : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ExtensionKeyMismatch(const std::string& message) : szErrorMessage("No extension found matches suplied key: " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}