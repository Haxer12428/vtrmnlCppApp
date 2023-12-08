#include "../Cmd.h"

void* Cmd::COMMAND_MEMORY_USAGE(
	const std::vector<std::string>& ARGUMENTS
) {
	if (
		this->COMMAND_MEMORY_USAGE_GRAPH->IsShown()
		) {
		this->COMMAND_MEMORY_USAGE_GRAPH->Show(false); return 0;
	}
	this->COMMAND_MEMORY_USAGE_GRAPH->Show(true); return 0;
}