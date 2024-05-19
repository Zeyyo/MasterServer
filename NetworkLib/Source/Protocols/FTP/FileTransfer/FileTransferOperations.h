#pragma once

namespace FileTransferOperations
{
	bool ReceiveFileSecure(SOCKET socket, Base64FileDataSecure& kFileData);
	bool ReceiveFile(SOCKET socket, Base64FileData& kFileData);
	bool TransmitFile(SOCKET socket, std::string& szFileNam);
}