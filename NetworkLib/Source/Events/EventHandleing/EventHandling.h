#pragma once
namespace Events::EventHandling
{
	void LogEvent(bool show, void(*func)(bool));
}