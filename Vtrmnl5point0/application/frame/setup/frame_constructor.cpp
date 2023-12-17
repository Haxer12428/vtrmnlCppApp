#include "../frame.h"

frame::frame(
	const std::string& name
) : wxFrame(nullptr, wxID_ANY, name)
{
	this->setup_config();
	this->setup_binds();

	SetBackgroundStyle(wxBG_STYLE_PAINT);

	std::vector<std::string> folders;

	this->Show();
}