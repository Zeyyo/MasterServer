#pragma once

#define DEFAULT_HEADER_PREFIX_LEN 3
#define DEFAULT_HEADER_PREFIX_BUFFER_LEN 5

namespace Helpers
{
	int ReveiveHeaderPrefix(SOCKET socket, WORD len = DEFAULT_HEADER_PREFIX_LEN, WORD bufferLen = DEFAULT_HEADER_PREFIX_BUFFER_LEN);
}


