#include "pch.h"
#include "EventHandleing.h"

namespace Events::EventHandling
{
	void LogEvent(bool show, void(*func)(bool))
	{
		func(show);
	}
}