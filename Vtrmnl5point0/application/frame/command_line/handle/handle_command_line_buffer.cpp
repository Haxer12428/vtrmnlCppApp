#include "../../frame.h"

const void frame::handle_command_line_buffer_format(
	const std::vector<std::string>& buffer, const int &maximal_size_x
) {
	std::vector<std::string> buffer_formated = buffer; 

	wxClientDC dc = wxClientDC(this);
	dc.SetFont(this->draw_command_line_font);


	while (
		true
		) {
		bool made_changes = false; 
		std::vector<std::string> buffer_cache;

		for (
			std::string current_buffer_line : buffer_formated
			) {
			const int current_buffer_line_size_x = dc.GetTextExtent(current_buffer_line).x;

			if (
				current_buffer_line_size_x <= maximal_size_x
				) {
				buffer_cache.push_back(current_buffer_line);
			}
			else {
				std::string buffer_line_cut = current_buffer_line;
				do {
					if (
						dc.GetTextExtent(buffer_line_cut).x <= maximal_size_x
						) {
						buffer_cache.push_back(buffer_line_cut);
						buffer_cache.push_back(current_buffer_line.substr(buffer_line_cut.length()));
						break; 
					}

					buffer_line_cut.resize(buffer_line_cut.length() - 1);

					made_changes = true; 
				} while (
					true
					);
			}
		}

		buffer_formated = buffer_cache;
		if (
			!made_changes
			) break; 
	}

	this->draw_command_line_buffer_formated = buffer_formated;
}

const void frame::handle_command_line_buffer_push_line(
	const std::string& buffer
) {
	this->draw_command_line_buffer_original.push_back(
		buffer
	); 

	this->handle_command_line_buffer_format(this->draw_command_line_buffer_original, this->draw_command_line_text_help_get_area_size().x);
	this->Refresh(); 
}