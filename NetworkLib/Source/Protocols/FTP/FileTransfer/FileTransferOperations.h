#pragma once

namespace FileTransferOperations
{
	bool ReceiveFile(SOCKET socket, const FileData& kFileData);
	bool TransmitFile(SOCKET socket, std::string& szFileNam);
}
