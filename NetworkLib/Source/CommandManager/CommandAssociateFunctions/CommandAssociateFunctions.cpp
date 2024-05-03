#include "NEtw_pch.h"
#include "CommandAssociateFunctions.h"

namespace Commands
{
	void DoFileAcquire(const SOCKET socket, FileData& fileData)
	{
		bool bFileAcquireSuccess = FileTransferOperations::ReceiveFile(socket, fileData);
	}

	void DoFileDispatch(const SOCKET socket, std::string& szFileName)
	{
		bool bFileDispatchSuccess = FileTransferOperations::TransmitFile(socket, szFileName);
	}
}