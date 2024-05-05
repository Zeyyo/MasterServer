#pragma once

struct Header
{
	Header(
		std::string headerData, 
		size_t headerSize) 
		: 
		headerData(headerData), 
		headerSize(headerSize)
	{}
	std::string headerData;
	size_t headerSize;
};