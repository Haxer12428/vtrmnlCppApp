#include "../Engine.h"

Engine::Memory::ofProcess::ofProcess(
	Engine::Process Process
) : Process(Process) {

}

const double Engine::Memory::ofProcess::Usage(
	Engine::Memory::FORMAT _Format
) {
	HANDLE PROCESS_HANDLE = this->GetProcessHandle(); 
	PROCESS_MEMORY_COUNTERS_EX PMC;

	GetProcessMemoryInfo(PROCESS_HANDLE, (PROCESS_MEMORY_COUNTERS*)&PMC, sizeof PMC);

	return static_cast<double>(PMC.PrivateUsage / _Format);
}