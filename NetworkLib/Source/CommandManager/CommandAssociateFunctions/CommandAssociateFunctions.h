#pragma once
#include "pch.h"
#include "Types/FileTypes.h"
#include "Protocols/FTP/FileTransfer/FileTransferOperations.h"

namespace Commands
{
	void DoFileAcquire(const SOCKET socket, FileData& fileData);
	void DoFileDispatch(const SOCKET socket, std::string& szFileName);
}