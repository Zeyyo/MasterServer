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
		std::string szName,
		size_t nSize,
		std::string szExtension,
		std::string szKey,
		std::string szIv)
		:
		szName(szName),
		nSize_(nSize),
		szExtension(szExtension),
		szKey(szKey),
		szIv(szIv)
	{ 
		pPackagedBinary->length = nSize_;
	}
	std::string szName;
	std::string szExtension;

	std::string szKey;
	std::string szIv;

	std::unique_ptr<PackagedFileBinary> pPackagedBinary = std::make_unique<PackagedFileBinary>();
	std::unique_ptr<FileBinary> pBinary = std::make_unique<FileBinary>();
private:
	size_t nSize_;
};

struct Base64FileDataSecure
{
	Base64FileDataSecure() = default;
	Base64FileDataSecure(
		std::string szName, 
		size_t nSize, 
		std::string szExtension,
		std::string szKey,
		std::string szIv) 
		:
		szName(szName),
		nSize_(nSize),
		szExtension(szExtension),
		szKey(szKey),
		szIv(szIv) 
	{
		pPackagedBinary->length = nSize_;
	}
	std::string szName;
	std::string szExtension;

	std::string szKey;
	std::string szIv;

	std::unique_ptr<PackagedFileBinary> pPackagedBinary = std::make_unique<PackagedFileBinary>();
	std::unique_ptr<FileBinary> pBinary = std::make_unique<FileBinary>();
private:
	size_t nSize_;
};