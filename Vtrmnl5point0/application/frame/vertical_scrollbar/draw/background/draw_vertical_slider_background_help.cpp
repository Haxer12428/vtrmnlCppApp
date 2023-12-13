#include "../../../frame.h"

const wxPoint frame::draw_vertical_scrollbar_help_get_background_starting_position() {
	return wxPoint(
		this->GetClientSize().x - this->draw_vertical_scrollbar_background_reserved_space, this->draw_mouse_interactive_panel_reserved_space_total
		);
}

const wxPoint frame::draw_vertical_scrollbar_help_get_background_final_position() {
	const wxSize window_size = this->GetClientSize(); 
	return wxPoint(
		window_size.x, window_size.y
	);
}

const wxSize frame::draw_vertical_scrollbar_help_get_background_size() {
	const wxPoint diff_between_staring_and_final = (
		this->draw_vertical_scrollbar_help_get_background_final_position() - this->draw_vertical_scrollbar_help_get_background_starting_position()
		);
	return wxSize(
		diff_between_staring_and_final.x, diff_between_staring_and_final.y
	);
}