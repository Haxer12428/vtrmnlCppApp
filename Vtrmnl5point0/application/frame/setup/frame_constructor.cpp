#include "../frame.h"

frame::frame(
	const std::string& name
) : wxFrame(nullptr, wxID_ANY, name)
{
	this->setup_config();
	this->setup_binds();

	SetBackgroundStyle(wxBG_STYLE_PAINT);

	const bool as_administrator = engine::process::current().is_administrator();

	if (
		!as_administrator
		) {
		this->handle_command_line_buffer_push_line(
			"\aFFFF00warning:\aFFFFFF program ain't running in \aFF0000administrator\aFFFFFF mode"
		);
		
		this->handle_command_line_buffer_format(this->draw_command_line_buffer_original, this->draw_command_line_text_help_get_area_size().x);
	}

	this->handle_command_line_buffer_push_line(
		""
	);

	std::vector<std::string> folders;

	this->Show();
}