#pragma once
#include "NEtw_pch.h"
#include "Types/File.h"
#include "Protocols/FTP/FileTransfer/FileTransferOperations.h"


namespace CommandManager::Commands
{
	void DoFileAcquireSecure(const SOCKET socket, Base64FileDataSecure& fileData);
	void DoFileAcquireSecure(const SOCKET socket, Base64FileDataSecure& fileData, std::string& id);
	void DoFileAcquire(const SOCKET socket, Base64FileData& fileData);
	void DoFileDispatch(const SOCKET socket, std::string& szFileName);
}