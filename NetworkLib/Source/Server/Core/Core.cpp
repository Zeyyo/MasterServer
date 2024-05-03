#include "NEtw_pch.h"

#include "Events/Logger/OstreamLogger.h"
#include "Events/Exceptions/ServerCoreExceptions.h"

#include "Includes/Core.h"

namespace NetworkLibrary 
{
	void Core::InitializeCore(WORD version)
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

	void Core::InitializeWinsock(WORD version)
	{
		dwResult = WSAStartup(version, &wsaData_);
		if (dwResult != 0)
			throw Exceptions::ServerCoreExceptions::CoreInitializationException(dwResult);
		else
			Logger::LOG[Logger::Level::Info] << "Core initialized!" << Logger::endl;
	}
}