#pragma once
#include "NEtw_pch.h"
#include "SocketEvents.h"

namespace SocketUtils
{
    struct ChunkData
    {
        const char* inputBuffer;
        int inputLength;
        int chunkSize;
    };
}