#pragma once
#include <string>

struct FileData
{
	FileData() = default;
	FileData(std::string szFileName, size_t FileSize, std::string szFileExtension) :
		szFileName(szFileName),
		nFileSize(FileSize),
		szFileExtension(szFileExtension) { }

	std::string szFileName;
	size_t nFileSize;
	std::string szFileExtension;
	char* prawBinaryFileData = NULL;
};