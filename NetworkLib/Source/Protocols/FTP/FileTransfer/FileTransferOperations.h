#pragma once

namespace FileTransferOperations
{
	bool ReceiveFile(SOCKET socket, Base64FileData& kFileData);
	bool ReceiveFile(SOCKET socket, FileData& kFileData);
	bool TransmitFile(SOCKET socket, std::string& szFileNam);
}