#include "NEtw_pch.h"
#include "CommandAssociateFunctions.h"

namespace CommandManager::Commands
{
	void DoFileAcquireSecure(const SOCKET socket, Base64FileDataSecure& fileData)
	{
		bool bFileAcquireSuccess = FileTransferOperations::ReceiveFileSecure(socket, fileData);
	}

	void DoFileAcquireSecure(const SOCKET socket, Base64FileDataSecure& fileData, std::string& id)
	{
		bool bFileAcquireSuccess = FileTransferOperations::ReceiveFileSecure(socket, fileData, id);
	}

	void DoFileAcquire(const SOCKET socket, Base64FileData& fileData)
	{
		bool bFileAcquireSuccess = FileTransferOperations::ReceiveFile(socket, fileData);
	}

	void DoFileDispatch(const SOCKET socket, std::string& szFileName)
	{
		bool bFileDispatchSuccess = FileTransferOperations::TransmitFile(socket, szFileName);
	}
}