#pragma once
#include "NEtw_pch.h"
#include "Types/File.h"
#include "Protocols/FTP/FileTransfer/FileTransferOperations.h"

namespace Commands
{
	void DoFileAcquire(const SOCKET socket, FileData& fileData);
	void DoFileDispatch(const SOCKET socket, std::string& szFileName);
}