#include <iostream>
#include <Windows.h>

#include "Includes/Core.h"
#include "Includes/WorkerPool.h"
#include "Includes/ConnectionManager.h"
#include "Includes/Types/HandlerModule.h"
#include "Includes/Types/Time.h"
#include "Includes/Filters.h"
//#include "Includes/Logger.h"

using NetworkLibrary::ModuleType;

int main()
{
    Filters::timeFormatFilter = NetworkLibrary::TimeFormat::TIME;

    NetworkLibrary::Core core(MAKEWORD(2,2));
    NetworkLibrary::ThreadPool threadPool(20);
    NetworkLibrary::ConnectionManager conManager(ModuleType::FTP);

    while (1)
    {

    }
    std::cin.get();
    return 0;
}