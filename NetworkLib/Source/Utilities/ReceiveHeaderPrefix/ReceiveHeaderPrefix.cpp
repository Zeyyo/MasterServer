#include "NEtw_pch.h"

#include "Utilities/SocketOperations/SocketOperations.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Events/Exceptions/NetworkOperationExceptions.h"
#include "Events/Exceptions/CryptoOperationException.h"
#include "Events/Logger/OstreamLogger.h"
#include "Crypto/CryptoService.h"

#include "ReceiveHeaderPrefix.h"

namespace Helpers
{
    int ReveiveHeaderPrefix(SOCKET socket, WORD len, WORD bufferLen)
    {
        char* pHeaderPrefixBuffer = new char[bufferLen];
        std::memset(pHeaderPrefixBuffer, 0, bufferLen);
        const char* pHeaderPrefixBufferDecrypted = new char[len];

        try
        {
            Utilities::SocketOperations::Receive(
                socket,
                pHeaderPrefixBuffer,
                len);
        }
        catch (Exceptions::SocketOperationExceptions::ReceiveTimeOutException& e)
        {
            throw Exceptions::NetworkOperationExceptions::FailedToReceiveHeaderPrefixException("");
        }
        catch (Exceptions::SocketOperationExceptions::SocketBufferEmptyException& e)
        {
            std::string szErrorMessage = e.GetError();
            Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at ReveiveHeaderPrefix()." << Logger::endl;
        }

        bool allDigits = true;
        for (size_t i = 0; i < len; ++i) {
            if (!std::isdigit(pHeaderPrefixBuffer[i])) {
                allDigits = false;
                break;
            }
        }

        if (allDigits)
        {
            int prefixLen = std::atoi(pHeaderPrefixBuffer);
            return prefixLen;
        }
        else { throw Exceptions::NetworkOperationExceptions::InvalidHeaderPrefixException(""); }
        return -1;
    }
}