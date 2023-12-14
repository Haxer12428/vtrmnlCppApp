#include "../../../frame.h"

const wxSize frame::draw_vertical_scrollbar_help_get_movable_size() {
	const wxSize background_size = this->draw_vertical_scrollbar_help_get_background_size(); 
	
	const wxSize total_size = wxSize(
		background_size.x * this->draw_vertical_scrollbar_movable_size_factor_x, (background_size.y - this->draw_vertical_scrollbar_movable_area_dif) * this->draw_vertical_scrollbar_movable_size_factor_y
	);

	return total_size;
}

const wxPoint frame::draw_vertical_scrollbar_help_get_movable_starting_position() {
	const wxPoint scrollbar_background_starting_position = this->draw_vertical_scrollbar_help_get_background_starting_position();
	
	const wxPoint movable_starting_position = wxPoint(
		scrollbar_background_starting_position.x, scrollbar_background_starting_position.y + this->draw_vertical_scrollbar_movable_area_dif / 2
	);
	
	return movable_starting_position; 
}

const wxPoint frame::draw_vertical_scrollbar_help_get_movable_current_position() {
	const wxPoint movable_starting_position = this->draw_vertical_scrollbar_help_get_movable_starting_position(); 
	const wxSize background_size = this->draw_vertical_scrollbar_help_get_background_size();

	const wxSize total_size = wxSize(
		background_size.x, background_size.y + this->draw_vertical_scrollbar_movable_area_dif
	);

	return wxPoint(
		movable_starting_position.x + float(float(total_size.x) * float(this->draw_vertical_scrollbar_movable_size_factor_x))/2, movable_starting_position.y + this->draw_vertical_scrollbar_movable_scroll_amount
	);
}

const wxPoint frame::draw_vertical_scrollbar_help_get_movable_final_position() {
	const wxSize background_size = this->draw_vertical_scrollbar_help_get_background_size();
	const wxPoint starting_position = this->draw_vertical_scrollbar_help_get_movable_starting_position(); 

	const wxSize total_size = wxSize(
		background_size.x, background_size.y + this->draw_vertical_scrollbar_movable_area_dif
	);

	return (
		starting_position + total_size
		);
}

const int frame::draw_vertical_scollbar_help_get_maximal_scroll() {
	const wxPoint movable_size_full = (
		this->draw_vertical_scrollbar_help_get_movable_final_position() - this->draw_vertical_scrollbar_help_get_movable_starting_position()
		); 

	const wxSize movable_size = this->draw_vertical_scrollbar_help_get_movable_size(); 

	const wxSize movable_dif = (
		wxSize(movable_size_full.x, movable_size_full.y) - movable_size
		);

	return movable_dif.y - this->draw_vertical_scrollbar_movable_area_dif*2;
}

const float frame::draw_vertical_scrollbar_help_get_movable_scroll_procentage() {
	return float(
		float(this->draw_vertical_scrollbar_movable_scroll_amount) / float(this->draw_vertical_scollbar_help_get_maximal_scroll())
		);
}