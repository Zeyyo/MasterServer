#pragma once

namespace NetworkLibrary
{
	class Core
	{
	public:
		Core(WORD version)
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
