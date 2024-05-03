#pragma once
namespace Events::ErrorHandling
{    
	void FatalError(bool show, DWORD dwErrCode, void(*func)(bool, DWORD));
}