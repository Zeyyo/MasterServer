#include "pch.h"
#include "Session.h"

void NetworkLibrary::Session::CloseAndDestruct()
{
	closesocket(socket_);
	Logger::LOG[Logger::Level::Warning] << "Session terminated!" << Logger::endl;
	//delete this;
}
