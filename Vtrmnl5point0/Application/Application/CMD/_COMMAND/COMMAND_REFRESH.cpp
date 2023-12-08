#include "../Cmd.h"

void* Cmd::COMMAND_REFRESH(
	const std::vector<std::string>& ARGUMENTS
) {
	this->SETUP_CONFIG_HANDLE(this->_AT);
	this->Update(); this->Refresh(); return 0;
}