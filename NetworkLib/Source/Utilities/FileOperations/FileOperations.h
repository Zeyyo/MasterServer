#pragma once

namespace Utilities::FileOperations
{
	void StoreFile(
		const std::string& szfileName, 
		const std::string& fileExtension, 
		const char* fileDataBuffer,
		size_t length,
		const std::string& storageLocation);

	FileData LoadFile(
		const std::string& szfileName,
		const std::string& szLoadStorageLocation);

	bool SaveFile(
		Base64FileData& kFileData,
		std::string location);

	bool SaveFileSecure(
		Base64FileDataSecure& kFileData,
		std::string location);

	bool SaveFileSecure(
		Base64FileDataSecure& kFileData,
		std::string location,
		std::string& id);
}
