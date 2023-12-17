#include "../../../frame.h"

const wxPoint frame::draw_command_line_cursor_help_get_starting_position(
	const std::vector<int> cursor_position_in_buffer, wxAutoBufferedPaintDC& dc
) {
	const wxPoint line_position = this->draw_command_line_text_help_get_current_line_position(
		dc, draw_command_line_cursor_position_in_buffer[0]
	);

	return line_position;
}

const wxSize frame::draw_command_line_cursor_help_get_size(
	const std::vector<int> cursor_position_in_buffer, wxAutoBufferedPaintDC& dc
) {
	const std::string line = this->draw_command_line_buffer_formated[cursor_position_in_buffer[0]];
	const std::string line_char = std::string(1, line[cursor_position_in_buffer[1]]);

	return dc.GetTextExtent(line_char);
}