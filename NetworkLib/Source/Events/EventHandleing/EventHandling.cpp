#include "NEtw_pch.h"
#include "EventHandling.h"

namespace Events::EventHandling
{
	void LogEvent(bool show, void(*func)(bool))
	{
		func(show);
	}
}