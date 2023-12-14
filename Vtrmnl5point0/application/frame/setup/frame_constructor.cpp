#include "../frame.h"

frame::frame(
	const std::string& name
) : wxFrame(nullptr, wxID_ANY, name)
{
	this->setup_config();
	this->setup_binds();

	SetBackgroundStyle(wxBG_STYLE_PAINT);

	std::vector<std::string> folders;

	for (
		const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("C:\\")
		) {
		folders.push_back(entry.path().string());
	}

	for (
		std::string str : folders
		) {
		try {
			for (
				const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(str)
				) {
				this->draw_command_line_buffer_formated.push_back(entry.path().string());
			}
		}
		catch (
			const std::exception& /*ex*/
			) {

		}
	}

	this->Show();
}