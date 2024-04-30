// Server

#include <iostream>
#include "Server/config.h"
#include "Blankets/rot19/rot19.h"
#include "Server/Core/Core.h"
#include "Server/ConnectionManager/ConnectionManager.h"

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