#pragma once

namespace Events::EventHandling
{
    inline bool verbose = false;
    void LogEvent(bool show, void(*func)(bool));
}