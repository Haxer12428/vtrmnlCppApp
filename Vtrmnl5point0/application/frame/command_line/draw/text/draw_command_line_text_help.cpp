#include "../../../frame.h"

const wxPoint frame::draw_command_line_text_help_get_starting_position() {
	const wxPoint text_push = wxPoint(
		this->draw_command_line_text_push_x, this->draw_command_line_text_push_y
	);

	return wxPoint(
		text_push.x, this->draw_mouse_interactive_panel_reserved_space_total + text_push.y
	);
}

const wxPoint frame::draw_command_line_text_help_get_final_position() {
	const wxSize window_size = this->GetClientSize();

	return wxPoint(
		window_size.x - this->draw_vertical_scrollbar_help_get_background_size().x, window_size.y
	);
}

const int frame::draw_command_line_text_help_get_text_line_height(
	wxAutoBufferedPaintDC& dc
) {
	const wxSize text_size = dc.GetTextExtent("This is regular TextLine");
	
	return (
		text_size.y + this->draw_command_line_text_spacing
		);
}

const wxPoint frame::draw_command_line_text_help_get_current_line_position(
	wxAutoBufferedPaintDC& dc, const int buffer_position
) {
	const int line_height = this->draw_command_line_text_help_get_text_line_height(dc);
	const int all_lines_height = line_height * this->draw_command_line_buffer_formated.size(); 

	const int line_starting_point_x = this->draw_command_line_text_help_get_starting_position().x;

	const int command_line_text_area_height = (
		this->draw_command_line_text_help_get_final_position().y - this->draw_command_line_text_help_get_starting_position().y
		);

	const int maximal_scroll = all_lines_height - command_line_text_area_height;

	if (
		maximal_scroll <= 0
		) return wxPoint(
			line_starting_point_x, line_height * buffer_position
		); 

	return wxPoint(
		line_starting_point_x,
		int(
			(line_height * buffer_position) - maximal_scroll * this->draw_vertical_scrollbar_help_get_movable_scroll_procentage()
			)
		);
}

const wxSize frame::draw_command_line_text_help_get_area_size() {
	const wxPoint area = (
		this->draw_command_line_text_help_get_final_position() - this->draw_command_line_text_help_get_starting_position()
		);
	return wxSize(
		area.x, area.y
	);
}

const std::vector<frame::draw_command_line_colored_text> frame::draw_command_line_text_help_parse_text_with_color_from_string(
	const wxString& buffer
) const {
	std::vector<frame::draw_command_line_colored_text> parsed; 

	std::string remaining_buffer = buffer.ToStdString(); 

	const size_t hex_color_size = 6; 
	const size_t escape_size = 2;
	const size_t total_size = hex_color_size + escape_size;

	const size_t first_escape_found = engine::string(remaining_buffer).find_phrase("\a");

	if ( // no colors 
		first_escape_found == std::string::npos
		) {
		frame::draw_command_line_colored_text segment; 

		segment.text = remaining_buffer; 
		segment.color_hex = "";

		parsed.push_back(segment);

		return parsed; 
	}

	if ( // first segment has no color 
		first_escape_found != 0
		) {
		frame::draw_command_line_colored_text segment; 

		segment.text = remaining_buffer.substr(0, first_escape_found); 
		segment.color_hex = "";

		parsed.push_back(segment);

		remaining_buffer = remaining_buffer.substr(first_escape_found);
	}

	do {
		// escapes 
		const size_t escape_found = engine::string(remaining_buffer).find_phrase("\a");
		const size_t next_escape_found = engine::string(remaining_buffer.substr(escape_found + escape_size)).find_phrase("\a");

		// main's 
		std::string current_segment_text = remaining_buffer;
		const std::string current_segment_color_hex = remaining_buffer.substr(escape_size - 1, hex_color_size);

		if ( // last line 
			next_escape_found != std::string::npos
			) {
			current_segment_text.resize(next_escape_found + escape_size);
		}

		current_segment_text = current_segment_text.substr(total_size - 1);

		// segment 
		frame::draw_command_line_colored_text segment; 

		segment.text = current_segment_text;
		segment.color_hex = current_segment_color_hex; 

		parsed.push_back(segment);

		// handle buffer change 
		remaining_buffer = remaining_buffer.substr(current_segment_text.length() + total_size - 1);
	} while (
		!remaining_buffer.empty()
		);

	return parsed; 
}