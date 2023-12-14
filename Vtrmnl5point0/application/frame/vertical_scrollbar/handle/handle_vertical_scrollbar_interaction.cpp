#include "../../frame.h"

void frame::handle_vertical_scrollbar_interaction(
	wxMouseEvent& evt 
) {
	if (
		!this->handle_vertical_scrollbar_in_drag
		) return;

	if (
		!evt.LeftIsDown()
		) {
		this->handle_vertical_scrollbar_in_drag = false; return; 
	}

	const wxPoint mouse_position = evt.GetPosition(); 

	const int mouse_scroll = (
		mouse_position.y - this->draw_vertical_scrollbar_help_get_movable_starting_position().y
		);

	const int mouse_dif = this->draw_vertical_scrollbar_movable_scroll_dif;

	this->draw_vertical_scrollbar_movable_scroll_amount = (
		std::max(0, std::min(this->draw_vertical_scollbar_help_get_maximal_scroll(), mouse_scroll - mouse_dif))
		);

	//wxLogMessage("asd");
	this->Refresh();
	evt.Skip();
}

void frame::handle_vertical_scrollbar_interaction_start(
	wxMouseEvent& evt
) {
	wxPoint mouse_position = evt.GetPosition();
	
	const wxPoint starting_position = this->draw_vertical_scrollbar_help_get_movable_current_position();

	const wxPoint final_position = starting_position + this->draw_vertical_scrollbar_help_get_movable_size(); 

	if (!(
		starting_position.x <= mouse_position.x && mouse_position.x <= final_position.x &&
		starting_position.y <= mouse_position.y && mouse_position.y <= final_position.y
		)) {
		evt.Skip(); return;
	}

	const int mouse_dif = (
		mouse_position.y - this->draw_vertical_scrollbar_help_get_movable_current_position().y
		);

	this->draw_vertical_scrollbar_movable_scroll_dif = mouse_dif;

	this->handle_vertical_scrollbar_in_drag = true; 
}