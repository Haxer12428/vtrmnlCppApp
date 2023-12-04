#include "sdl.h"

Sdl::Memory::Memory()
{
	this->MemoryInfo.dwLength = sizeof this->MemoryInfo;
	GlobalMemoryStatusEx(&this->MemoryInfo);
}

const double Sdl::Memory::GetTotalMemory(
	Sdl::Memory::Format Format
) {
	return static_cast<double>(this->MemoryInfo.ullTotalPhys) / Format;
}

const double Sdl::Memory::GetMemoryUsage(
	Sdl::Memory::Format Format
) {
	return (this->GetTotalMemory(Format) - (static_cast<double>(this->MemoryInfo.ullAvailPhys) / Format));
}

const double Sdl::Memory::GetMemoryUsageForCurrentProcess(
	Sdl::Memory::Format Format 
) {
	DWORD PID = GetCurrentProcessId();
	HANDLE ProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);

	if (
		ProcessHandle == NULL
		) return -1; 

	PROCESS_MEMORY_COUNTERS pmc;

	if (
		GetProcessMemoryInfo(ProcessHandle, &pmc, sizeof(pmc))
		) return pmc.WorkingSetSize / Format;

	return -1; 
}