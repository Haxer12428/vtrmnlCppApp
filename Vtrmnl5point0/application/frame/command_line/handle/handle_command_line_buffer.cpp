#include "../../frame.h"

const void frame::handle_command_line_buffer_format(
	const std::vector<std::string>& buffer, const int &maximal_size_x
) {
	if (
		buffer.size() == this->draw_command_line_buffer_formated.size() && std::equal(
			buffer.begin(), buffer.end(), this->draw_command_line_buffer_formated.begin()
		)) return;
	std::vector<std::string> buffer_formated = buffer; 

	wxClientDC dc = wxClientDC(this);
	dc.SetFont(this->draw_command_line_font);


	do {
		bool made_changes = false; 
		std::vector<std::string> buffer_cache; 
		
		for (
			std::string buffer_line : buffer_formated
			) {
			bool made_changes_this_line = false; 
			std::string buffer_line_cut = buffer_line;

			do {
				if (
					dc.GetTextExtent(buffer_line_cut).x <= maximal_size_x
					) {
					buffer_cache.push_back(buffer_line_cut);

					if (
						made_changes_this_line
						) buffer_cache.push_back(
							buffer_line.substr(buffer_line_cut.length())
						);
					
					break;
				}

				made_changes = true; made_changes_this_line = true; 
				buffer_line_cut.resize(buffer_line_cut.length() - 1);
			} while (
				true
				);
		}
			
		buffer_formated = buffer_cache;

		if (!made_changes)
			break;
	} while (
		true
		);

	this->draw_command_line_buffer_formated = buffer_formated;
}

const void frame::handle_command_line_buffer_push_line(
	const std::string& buffer
) {
	this->draw_command_line_buffer_formated.push_back(
		buffer
	); 

	this->Refresh(); 
}