#pragma once
#include "pch.h"

#include "Protocols/FTP/config.h"
#include "Types/FileTypes.h"
#include "Utilities/SocketOperations/SocketOperations.h"
#include "Utilities/FileOperations/FileOperations.h"
#include "Events/Exceptions/FileTransferHandlerExceptions.h"
#include "Events/Exceptions/FileOperationExceptions.h"

namespace FileTransferOperations
{
	bool ReceiveFile(SOCKET socket, const FileData& kFileData);
	bool TransmitFile(SOCKET socket, std::string& szFileNam);
}
