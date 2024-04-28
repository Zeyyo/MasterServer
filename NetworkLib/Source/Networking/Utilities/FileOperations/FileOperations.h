#pragma once
#include "pch.h"
#include "fstream"
#include "string"
#include <filesystem>

#include "Helpers/OperationHelper/OperationHelper.h"
#include "Events/Logger/OstreamLogger.h"
#include "Networking/Types/FileTypes.h"
#include "Events/Exceptions/FileOperationExceptions.h"

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
