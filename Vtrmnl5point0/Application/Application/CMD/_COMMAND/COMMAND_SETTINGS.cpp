#include "../Cmd.h"

void* Cmd::COMMAND_SETTINGS(
	const std::vector<std::string>& ARGUMENTS
) {
	wxString command = "notepad \"" + this->Config->GetPath().string() + "\"";
	wxExecute(command, wxEXEC_ASYNC);
}