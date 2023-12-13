#include "../../frame.h"

void frame::handle_mouse_interactive_panel_interaction(
	wxMouseEvent& evt
) {
	const wxPoint starting_position_of_mouse_panel_text = this->draw_mouse_interactive_panel_get_starting_position(); 
	const wxPoint mouse_position = evt.GetPosition();

	wxClientDC dc = wxClientDC(this);
	dc.SetFont(this->draw_mouse_interactive_panel_font);

	int text_positions_sum = 0; 

	for (
		std::string current_text : this->draw_mouse_interactive_panel_get_text_vector()
		) {
		const wxSize current_text_size = dc.GetTextExtent(current_text);

		const wxPoint current_text_starting_position = (
			starting_position_of_mouse_panel_text + wxPoint(text_positions_sum, 0)
			);

		const wxPoint current_text_final_position = (
			current_text_starting_position + wxPoint(current_text_size.x, this->draw_mouse_interactive_panel_reserved_space_total)
			);

		if (
			current_text_starting_position.x <= mouse_position.x && mouse_position.x <= current_text_final_position.x &&
			current_text_starting_position.y <= mouse_position.y && mouse_position.y <= current_text_final_position.y
			) {
			const bool function_response = this->assigned_function_find_and_call(
				current_text, this->argument_empty
			);

			if (
				!function_response
				) wxLogMessage(
					"Error: handle_mouse_interactive_panel_interaction\n(?) Failed to call function assigned to given element you'r interacting with."
				);
		}

		text_positions_sum += this->draw_mouse_interactive_panel_spacing_between_text + current_text_size.x;
	}

	evt.Skip(); 
}