#include "pch.h"
#include "ErrorHandling.h"

namespace Events::ErrorHandling
{
    void FatalError(bool show, DWORD dwErrCode, void(*func)(bool, DWORD))
    {
        func(show, dwErrCode);
    }
}
