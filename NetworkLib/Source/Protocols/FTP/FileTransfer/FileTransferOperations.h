#pragma once

namespace FileTransferOperations
{
	bool ReceiveFileSecure(SOCKET socket, Base64FileDataSecure& kFileData);
	bool ReceiveFileSecure(SOCKET socket, Base64FileDataSecure& kFileData, std::string& id);
	bool ReceiveFile(SOCKET socket, Base64FileData& kFileData);
	bool TransmitFile(SOCKET socket, std::string& szFileNam);
}