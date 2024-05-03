#pragma once
#include <sal.h>

namespace NetworkLibrary
{
	class Core
	{
	public:
		Core(_In_ WORD version)
		{
			InitializeCore(version);
		}
	private:
		void InitializeCore(WORD version);
		void InitializeWinsock(WORD version);

		WSADATA wsaData_;
		DWORD dwResult;
	};
}
