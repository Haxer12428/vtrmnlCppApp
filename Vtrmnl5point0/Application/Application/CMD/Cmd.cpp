#include "Cmd.h"

Cmd::Cmd(
	const std::string& _NAME, std::filesystem::path _ATv
) : wxFrame(nullptr, wxID_ANY, _NAME), _AT(_ATv) {

	wxImage::AddHandler(new wxPNGHandler);
	wxIcon AppIcon;
	AppIcon.CopyFromBitmap(wxBitmap(_ATv.string() + "\\icon.png", wxBITMAP_TYPE_PNG));

	this->SetIcon(AppIcon);

	this->HANDLE_UPDATE();
	this->SETUP_REGISTER_VARIABLES(_ATv);
	this->SETUP_CONFIG_HANDLE(_ATv);
	this->SETUP_BINDS();
	this->SETUP_COMMANDS();

	for (
		const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator("C:\\asio-1.28.0")
		) {
		this->COMMAND_LINE_HANDLE_PUSH_BUFFER_LINE(entry.path().string());
	}
	
	this->Show(true);

	std::thread T([&] {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->Refresh(); this->Update();
		});
	T.detach();
}