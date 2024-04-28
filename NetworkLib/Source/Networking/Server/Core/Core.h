#pragma once
#include "pch.h"

#include "Events/Logger/OstreamLogger.h"
#include "Events/Exceptions/ServerCoreExceptions.h"

namespace NetworkLibrary
{
	class Core
	{
	public:
		Core(WORD version)
		{
			try
			{
				InitializeWinsock(version);
			}
			catch (Exceptions::ServerCoreExceptions::CoreInitializationException& e)
			{
				std::string szErrorMessage = e.GetError();
				Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at Core()" << Logger::endl;
			}
		}
	private:
		void InitializeWinsock(WORD version);

		WSADATA wsaData_;
		DWORD dwResult;
	};
}
