#include "../engine.h"

const double engine::memory::get_usage(
	engine::memory::format format
) {
	const bool opened = this->open_process();
	if (!opened)
		return -1;

	const HANDLE process_handle = this->get_process();
	PROCESS_MEMORY_COUNTERS_EX process_mem_info; 

	GetProcessMemoryInfo(
		process_handle, (PROCESS_MEMORY_COUNTERS*)&process_mem_info, sizeof process_mem_info
	);

	return static_cast<double>(process_mem_info.PrivateUsage / format);
}