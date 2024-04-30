#pragma once
#include "pch.h"
#include "Types/FileTypes.h"
#include "Protocols/FTP/FileTransfer/FileTransferOperations.h"

namespace Commands
{
	void DoFileAcquire(SOCKET socket, FileData& fileData);
	void DoFileDispatch(SOCKET socket, std::string& szFileName);
}


