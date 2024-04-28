#pragma once
#include "pch.h"

namespace Events::ErrorHandling
{    
	void FatalError(bool show, DWORD dwErrCode, void(*func)(bool, DWORD));
}