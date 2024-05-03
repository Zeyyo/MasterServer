#pragma once

namespace Utilitis::FileOperations
{
	void StoreFile(
		const std::string& szfileName, 
		const std::string& fileExtension, 
		const char* fileDataBuffer, 
		const std::string& storageLocation);

	FileData LoadFile(
		const std::string& szfileName,
		const std::string& szLoadStorageLocation);
}
