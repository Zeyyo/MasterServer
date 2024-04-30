#include "pch.h"
#include "ConnectionManager.h"

void NetworkLibrary::ConnectionManager::InitializeConnectionManager()
{

}

void NetworkLibrary::ConnectionManager::AddIndividualSessionHandler(int handlerFlags)
{
	SessionHandler* pSessionHandler = new SessionHandler(handlerFlags, FILE_TRANSFER_PROTOCOL_PORT, DEFAULT_BACKLOG, ftpMod);
	pSessionHandler->InitializeSessionHandler();
}

void NetworkLibrary::ConnectionManager::RemoveIndividualSessionHandler(int handlerFlag)
{
	for (auto it = sessionHandlers.begin(); it != sessionHandlers.end(); ++it)
	{
		SessionHandler* pModule = reinterpret_cast<SessionHandler*>(it->pModule);
		if (pModule->GetModuleType() == handlerFlag) pModule->stop();
	}
}