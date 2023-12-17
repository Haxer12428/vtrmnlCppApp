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