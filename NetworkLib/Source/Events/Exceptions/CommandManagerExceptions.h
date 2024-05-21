#pragma once
#include <string>
#include <exception>

namespace Exceptions::CommandManagerExceptions
{
    class InvalidCommandPattern : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        InvalidCommandPattern(const std::string& message) : szErrorMessage("Invalid command pattern supplied: " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class CommandKeyMismatch : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        CommandKeyMismatch(const std::string& message) : szErrorMessage("No command suits supplied key: " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}