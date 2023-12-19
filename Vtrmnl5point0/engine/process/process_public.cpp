#include "../engine.h"


const bool engine::process::open_process() {
	this->process_handle = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, this->process_id
	);

	return this->process_handle != NULL;
}

const bool engine::process::close_process() {
	try {
		CloseHandle(this->process_handle);
	}
	catch (
		const std::exception& /*ex*/
		) {
		return false; 
	}

	return true; 
}

const bool engine::process::find_by_pid(
	const DWORD& pid
) {
	this->process_id = pid;

	if (this->open_process()) {
		this->close_process(); return true; 
	}

	return false;
}

const HANDLE engine::process::get_process() const {
	return this->process_handle;
}

const bool engine::process::find_by_name(
	const std::string& name
) {
	HANDLE process_snapshot; 
	PROCESSENTRY32 process32_entry; 

	process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (
		process_snapshot == INVALID_HANDLE_VALUE
		) return false; 

	process32_entry.dwSize = sizeof PROCESSENTRY32; 

	if (
		!Process32First(process_snapshot, &process32_entry)
		) {
		CloseHandle(process_snapshot); return false; 
	}

	do 
	{
		if (
			name == process32_entry.szExeFile
			) {
			this->process_id = (
				process32_entry.th32ProcessID
				);
			return true; 
		}
	} while (
		Process32Next(process_snapshot, &process32_entry)
		);

	return false;
}