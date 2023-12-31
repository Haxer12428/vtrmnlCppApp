#include "sdl.h"

Sdl::CPU::CPU()
{

}

const double Sdl::CPU::GetUsage() 
{
    FILETIME idleTime, kernelTime, userTime;

    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        return 0; // Return error value
    }

    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long idle = ((unsigned long long)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
    unsigned long long kernel = ((unsigned long long)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
    unsigned long long user = ((unsigned long long)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;

    unsigned long long totalTicks = kernel + user;
    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idle - _previousIdleTicks;

    double result = 1.0 - ((double)idleTicksSinceLastTime) / totalTicksSinceLastTime;

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idle;

    return result * 100.0;
}

const double Sdl::CPU::GetFrequency()
{
    return 0;
}