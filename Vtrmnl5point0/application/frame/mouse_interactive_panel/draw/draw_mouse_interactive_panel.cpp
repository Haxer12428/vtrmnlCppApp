#include "../../frame.h"

const void frame::draw_mouse_interactive_panel_main(
	wxAutoBufferedPaintDC& paint
) {

	this->draw_mouse_interactive_panel_update_reserved_space_total();
	this->draw_mouse_interactive_panel_background(paint); 
	this->draw_mouse_interactive_panel_text(paint); 

}

const std::vector<std::string> frame::draw_mouse_interactive_panel_get_text_vector() const {
	return { "(~)", "Settings", "Memory Usage", "Help" };
}

const std::string frame::draw_mouse_interactive_panel_get_text_string() const {
	std::string text_string = "";

	for (
		std::string str : this->draw_mouse_interactive_panel_get_text_vector()
		) {
		text_string += str; 
	}
	return text_string;
}

const void frame::draw_mouse_interactive_panel_update_reserved_space_total() {
	wxClientDC dc = wxClientDC(this);

	dc.SetFont(this->draw_mouse_interactive_panel_font);

	this->draw_mouse_interactive_panel_reserved_space_total = (
		dc.GetTextExtent(this->draw_mouse_interactive_panel_get_text_string()).y + this->draw_mouse_interactive_panel_reserved_space_user_extension
	);
}

const wxPoint frame::draw_mouse_interactive_panel_get_starting_position() const {
	const wxPoint mouse_interactive_panel_starting_centered_position = wxPoint(
		this->draw_mouse_interactive_panel_text_user_push_x, 0
	);
	return mouse_interactive_panel_starting_centered_position;
}

const void frame::draw_mouse_interactive_panel_text(
	wxAutoBufferedPaintDC& paint
) {
	paint.SetFont(this->draw_mouse_interactive_panel_font);

	const int mouse_interactive_panel_text_y = paint.GetTextExtent(
		this->draw_mouse_interactive_panel_get_text_string()).y;

	const wxPoint mouse_interactive_panel_starting_centered_position = wxPoint(
		this->draw_mouse_interactive_panel_text_user_push_x, (this->draw_mouse_interactive_panel_reserved_space_total / 2) - (mouse_interactive_panel_text_y / 2)
	);

	int mouse_interactive_text_summed = 0; 

	paint.SetTextForeground(wxColor(255, 255, 255));

	for (
		std::string mouse_interactive_panel_current_text : this->draw_mouse_interactive_panel_get_text_vector()
		) {
		const wxPoint mouse_interactive_panel_current_text_position = wxPoint(
			mouse_interactive_panel_starting_centered_position.x + mouse_interactive_text_summed, mouse_interactive_panel_starting_centered_position.y
		);

		paint.DrawText(
			mouse_interactive_panel_current_text, mouse_interactive_panel_current_text_position
		);

		mouse_interactive_text_summed += paint.GetTextExtent(mouse_interactive_panel_current_text).x + this->draw_mouse_interactive_panel_spacing_between_text;
	}
}

const void frame::draw_mouse_interactive_panel_background(
	wxAutoBufferedPaintDC& paint
) {
	const wxSize mouse_interactive_panel_background_size = wxSize(
		this->GetClientSize().x, this->draw_mouse_interactive_panel_reserved_space_total
	);

	const wxPoint mouse_interactive_panel_background_starting_position = wxPoint(0, 0);

	paint.SetBrush(this->draw_mouse_interactive_panel_background_color);
	paint.SetPen(this->draw_mouse_interactive_panel_background_color);

	paint.DrawRectangle(
		mouse_interactive_panel_background_starting_position, mouse_interactive_panel_background_size
	);
}