#ifndef NETW_PCH_H
#define NETW_PCH_H

#include "framework.h"

// LIBRARIES
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include <queue>

// GUARD
#define WIN32_LEAN_AND_MEAN
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#define _WINSOCKAPI_

// WINDOWS API
#include <Windows.h>
// WINSOCK
#include <Ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")

#endif //NETW_PCH_H
