#include "../Engine.h"

Engine::Process::Process() {

}

void Engine::Process::FindName(
	const std::string& Name
) {
	HANDLE SNAPSHOT = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 P32Entry;
	P32Entry.dwSize = sizeof P32Entry;

	if (
		Process32First(SNAPSHOT, &P32Entry)
		) {
		do {
			if (
				Name == P32Entry.szExeFile
				) {
				this->PID = P32Entry.th32ProcessID; return; 
			}
		} while (
			Process32Next(SNAPSHOT, &P32Entry)
			);
	} 
	throw Engine::Debug::Object(
		"Engine::Process::FindName -> Failed to find PE32Entry", Engine::Debug::FAIL
	);
}

void Engine::Process::FindPID(
	const DWORD& PID
) {
	this->PROCESS_HANDLE = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);

	if (
		this->PROCESS_HANDLE == NULL
		) throw Engine::Debug::Object("Engine::Process:FindPID -> Failed to create PROCESS_HANDLE;", Engine::Debug::FAIL);
}

HANDLE Engine::Process::GetProcessHandle()
{
	return this->PROCESS_HANDLE;
}