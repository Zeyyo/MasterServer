#pragma once
#include "Includes/conf.h"

namespace NetworkLibrary
{
    enum class ModuleType {
        FTP = FTP_MODULE,
        SMTP = SMTP_MODULE,
        TELNET = TELNET_MODULE,
        _COUNT = 3,
        begin = FTP,
        end = _COUNT
    };

    inline ModuleType operator|(ModuleType a, ModuleType b)
    {
        return static_cast<ModuleType>(static_cast<int>(a) | static_cast<int>(b));
    }
    inline int operator&(ModuleType a, ModuleType b)
    {
        return static_cast<int>(a) & static_cast<int>(b);
    }
}