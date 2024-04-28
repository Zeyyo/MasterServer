#include "pch.h"
#include "Core.h"

void NetworkLibrary::Core::InitializeWinsock(WORD version)
{
	dwResult = WSAStartup(version, &wsaData_);
	if (dwResult != 0)
		throw Exceptions::ServerCoreExceptions::CoreInitializationException(dwResult);
	else
		Logger::LOG[Logger::Level::Info] << "Core initialized!" << Logger::endl;
}