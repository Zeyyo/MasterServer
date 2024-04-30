#include "pch.h"
#include "Commands.h"

namespace Commands
{
	void DoFileAcquire(SOCKET socket, FileData& fileData)
	{
		bool bFileAcquireSuccess = FileTransferOperations::ReceiveFile(socket, fileData);
	}

	void DoFileDispatch(SOCKET socket, std::string& szFileName)
	{
		bool bFileDispatchSuccess = FileTransferOperations::TransmitFile(socket, szFileName);
	}
}