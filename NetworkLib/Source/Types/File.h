#pragma once
#include <string>

struct FileData
{
	FileData() = default;
	FileData(
		std::string szFileName,
		size_t FileSize, 
		std::string szFileExtension)
		:
		szFileName(szFileName),
		nFileSize(FileSize),
		szFileExtension(szFileExtension) 
	{ }
	std::string szFileName;
	size_t nFileSize;
	std::string szFileExtension;
	char* prawBinaryFileData = NULL;
};

struct Base64FileData
{
	Base64FileData() = default;
	Base64FileData(
		std::string szFileName, 
		size_t FileSize, 
		std::string szFileExtension,
		std::string szKey,
		std::string szIv) 
		:
		szFileName(szFileName),
		nFileSize(FileSize),
		szFileExtension(szFileExtension),
		szKey(szKey),
		szIv(szIv) 
	{ }
	std::string szFileName;
	size_t nFileSize;
	std::string szFileExtension;

	std::string szKey;
	std::string szIv;

	char* pBase64EncodedBinary = NULL;
};