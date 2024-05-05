#include "NEtw_pch.h"
#include "ZeroBuffer.h"

namespace Utilities::Memory
{
	void ZeroBufferMemory(char* buffer, size_t len)
	{
		memset(buffer, 0, len);
	}
}