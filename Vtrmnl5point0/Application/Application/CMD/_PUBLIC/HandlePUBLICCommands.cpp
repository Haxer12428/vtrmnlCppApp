#include "../Cmd.h"

const void Cmd::PUBLIC_COMMAND_PUSH(
	Cmd::COMMAND_STRUCT COMMAND
) {
	this->COMMAND_LIST.push_back(
		COMMAND
	);
}