#pragma once
#include <string>

struct FileBinary
{
	char* binary;
	size_t length;
};

struct PackagedFileBinary
{
	char* binary;
	size_t length;
};

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
	std::unique_ptr<FileBinary> pFileBinary = nullptr;

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

	std::unique_ptr<PackagedFileBinary> pPackagedFileBinary = std::make_unique<PackagedFileBinary>();
	std::unique_ptr<FileBinary> pFileBinary = std::make_unique<FileBinary>();
};

struct Base64FileDataSecure
{
	Base64FileDataSecure() = default;
	Base64FileDataSecure(
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

	std::unique_ptr<PackagedFileBinary> pPackagedFileBinary = std::make_unique<PackagedFileBinary>();
	std::unique_ptr<FileBinary> pFileBinary = std::make_unique<FileBinary>();
};