#pragma once

#include <string>
#include <exception>

namespace Exceptions::WorkerPoolExceptions
{
    class WorkerPoolInitializationException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WorkerPoolInitializationException(const std::string& errorDetails) :
            szErrorMessage("Worker pool initialization failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class WorkerInitializationException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WorkerInitializationException(const std::string& errorDetails) :
            szErrorMessage("Worker initialization failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class WorkerTerminationException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WorkerTerminationException(const std::string& errorDetails) :
            szErrorMessage("Worker termination failed: " + errorDetails) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };

    class WorkerPoolMissingException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WorkerPoolMissingException(const std::string& message) :
            szErrorMessage("Worker pool missing: " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
    };
}