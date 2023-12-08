#include "../../Cmd.h"

const void Cmd::COMMANDS_HANDLE_FIND_AND_CALL(
	const std::string& NAME, const std::vector<std::string>& ARGUMENTS
) {
	for (
		COMMAND_STRUCT COMMAND : this->COMMAND_LIST
		) {
		if (
			COMMAND.GetName() == NAME
			) {
			COMMAND.Call(this, ARGUMENTS); return; 
		}
	}
}