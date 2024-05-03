#pragma once
#include "Includes/conf.h"

namespace NetworkLibrary
{
    /// <summary>
    /// Enumerates the supported module types.
    /// </summary>
    enum class ModuleType {
        FTP =       FTP_MODULE,     /// FTP module type.
        SMTP =      SMTP_MODULE,    /// SMTP module type.
        TELNET =    TELNET_MODULE,  /// Telnet module type.
        _COUNT =    3,              /// Count of module types.
        begin =     FTP,            /// First module type.
        end =       _COUNT          /// End of module types.
    };

    /// <summary>
    /// Bitwise OR operator for combining module types.
    /// </summary>
    /// <param name="a">First module type.</param>
    /// <param name="b">Second module type.</param>
    /// <returns>The result of bitwise OR operation between module types.</returns>
    _Ret_range_(ModuleType::FTP, ModuleType::TELNET)
    inline ModuleType operator|(ModuleType a, ModuleType b)
    {
        return static_cast<ModuleType>(static_cast<int>(a) | static_cast<int>(b));
    }

    /// <summary>
    /// Bitwise AND operator for checking if module types intersect.
    /// </summary>
    /// <param name="a">First module type.</param>
    /// <param name="b">Second module type.</param>
    /// <returns>Bitwise AND result between module types.</returns>
    _Check_return_
    inline int operator&(ModuleType a, ModuleType b)
    {
        return static_cast<int>(a) & static_cast<int>(b);
    }
}