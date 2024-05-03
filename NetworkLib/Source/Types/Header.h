#pragma once

struct Header
{
	Header(
		const char* headerData, 
		size_t headerSize) 
		: 
		headerData(headerData), 
		headerSize(headerSize)
	{}
	const char* headerData;
	size_t headerSize;
};