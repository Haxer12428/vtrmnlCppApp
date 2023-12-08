#include "Cmd.h"

Cmd::Cmd(
	const std::string& _NAME, std::filesystem::path _ATv
) : wxFrame(nullptr, wxID_ANY, _NAME), _AT(_ATv) {

	this->HANDLE_UPDATE();
	this->SETUP_REGISTER_VARIABLES(_ATv);
	this->SETUP_CONFIG_HANDLE(_ATv);
	this->SETUP_BINDS();
	this->SETUP_COMMANDS();

	this->Show(true);
	
	std::thread T([&] {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->Refresh(); this->Update();
		});
	T.detach();
}