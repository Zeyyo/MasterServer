#pragma once
#include "pch.h"

namespace Exceptions::FileOperationExceptions
{
    class FileAlreadyExistsException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileAlreadyExistsException(const std::string& file) : szErrorMessage("File already exists: " + file) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class FileNotFoundException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileNotFoundException(const std::string& file) : szErrorMessage("File not found: " + file) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class FileLoadException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileLoadException(const std::string& file) : szErrorMessage("Failed to load file: " + file) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class FileLoadTimeoutException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileLoadTimeoutException(const std::string& details) : szErrorMessage("File loading timed out: " + details) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class FileStoreException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileStoreException(const std::string& file) : szErrorMessage("Failed to store file: " + file) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class FileCreateException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileCreateException(const std::string& file) : szErrorMessage("Failed to create file: " + file) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class FileCreateTimeOutException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        FileCreateTimeOutException(const std::string& details) : szErrorMessage("File creation timed out: " + details) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}