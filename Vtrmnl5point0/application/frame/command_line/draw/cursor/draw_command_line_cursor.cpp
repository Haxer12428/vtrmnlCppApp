#include "../../../frame.h"

const void frame::draw_command_line_cursor(
	wxAutoBufferedPaintDC& dc
) {
	std::vector<int> cursor_position_in_buffer = this->draw_command_line_cursor_position_in_buffer;

	if ( // not assigned? 
		cursor_position_in_buffer[0] == -1 || cursor_position_in_buffer[1] == -1
		) return; 

	
}