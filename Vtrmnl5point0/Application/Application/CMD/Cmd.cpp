#include "Cmd.h"

Cmd::Cmd(
	const std::string& _NAME, std::filesystem::path _ATv
) : wxFrame(nullptr, wxID_ANY, _NAME), _AT(_ATv) {

	this->SETUP_REGISTER_VARIABLES(_ATv);
	this->SETUP_CONFIG_HANDLE(_ATv);
	this->SETUP_BINDS();
	this->SETUP_COMMANDS();

	this->Show(true);
}