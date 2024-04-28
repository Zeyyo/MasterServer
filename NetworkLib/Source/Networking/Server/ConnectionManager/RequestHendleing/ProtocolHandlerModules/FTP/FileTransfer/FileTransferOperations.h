#pragma once
#include "pch.h"

#include "Networking/Server/ConnectionManager/RequestHendleing/ProtocolHandlerModules/FTP/config.h"
#include "Networking/Types/FileTypes.h"
#include "Networking/Utilities/SocketOperations/SocketOperations.h"
#include "Networking/Utilities/FileOperations/FileOperations.h"
#include "Events/Exceptions/FileTransferHandlerExceptions.h"
#include "Events/Exceptions/FileOperationExceptions.h"

namespace FileTransferOperations
{
	bool ReceiveFile(SOCKET socket, const FileData& kFileData);
	bool TransmitFile(SOCKET socket, std::string szFileNam);
}
