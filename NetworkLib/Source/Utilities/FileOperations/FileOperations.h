#pragma once

namespace Utilities::FileOperations
{
	void StoreFile(
		const std::string& szfileName, 
		const std::string& fileExtension, 
		const std::string& fileDataBuffer,
		const std::string& storageLocation);

	FileData LoadFile(
		const std::string& szfileName,
		const std::string& szLoadStorageLocation);
}
