#pragma once
#include "pch.h"

namespace Events::EventHandling
{
	void LogEvent(bool show, void(*func)(bool));
}