#include "../Engine.h"

Engine::Memory::Memory() {
	this->MemoryStatus.dwLength = sizeof this->MemoryStatus;
}

void Engine::Memory::Update() {
	GlobalMemoryStatusEx(&this->MemoryStatus);
}

const double Engine::Memory::GetAllocated(
	Engine::Memory::FORMAT _Format
) {
	this->Update(); return static_cast<double>(this->MemoryStatus.ullTotalPhys / _Format);
}

const double Engine::Memory::GetUsed(
	Engine::Memory::FORMAT _Format
) {
	this->Update(); return static_cast<double>(
		(this->MemoryStatus.ullTotalPhys - this->MemoryStatus.ullAvailPhys) / _Format
	);
}

const double Engine::Memory::GetFree(
	Engine::Memory::FORMAT _Format
) {
	this->Update(); return static_cast<double>(this->MemoryStatus.ullAvailPhys / _Format);
}

std::string Engine::Memory::GetProcessWithHighestMemoryConsumption(
	std::vector<std::string> _SKIP
) {
	HANDLE SNAPSHOT = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 P32Entry;
	P32Entry.dwSize = sizeof P32Entry;

	std::string _P32SelectedPID = ""; long long _P32HighestConsumption = 0;

	if (
		Process32First(SNAPSHOT, &P32Entry)
		) {
		do {
			if (
				Engine::Vector::Find<std::string>(_SKIP, P32Entry.szExeFile) == -1
				) {
				long long _CONSUMPTION;

				Engine::Process P32Engine = Engine::Process();
				P32Engine.FindName(P32Entry.szExeFile);
				//P32Engine.FindPID(9080);

				_CONSUMPTION = static_cast<long long>(Engine::Memory::ofProcess(P32Engine).Usage(Engine::Memory::MB));

				if (
					_CONSUMPTION > _P32HighestConsumption
					) {
					_P32HighestConsumption = _CONSUMPTION; 
					_P32SelectedPID = P32Entry.szExeFile;
				}
			}
		} while (
			Process32Next(SNAPSHOT, &P32Entry)
			);
	}

	return _P32SelectedPID;
}