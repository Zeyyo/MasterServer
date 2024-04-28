// Server

#include <iostream>
#include "Networking/Server/config.h"
#include "Blankets/rot19/rot19.h"
#include "Networking/Server/Core/Core.h"
#include "Networking/Server/ConnectionManager/ConnectionManager.h"

using NetworkLibrary::ModuleType;

int main()
{
    NetworkLibrary::Core core(MAKEWORD(2,2));
    NetworkLibrary::ThreadPool threadPool(20);
    NetworkLibrary::ConnectionManager conManager(ModuleType::FTP);
    //threadPool.TerminateIndividualWorkers(2);

    while (1)
    {

    }
    std::cin.get();
    return 0;
}