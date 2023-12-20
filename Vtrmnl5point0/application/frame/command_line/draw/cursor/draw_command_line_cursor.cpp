#include "../../../frame.h"

const void frame::draw_command_line_cursor(
	wxAutoBufferedPaintDC& dc
) {
	if (
		this->draw_command_line_buffer_formated.size() == 0
		) return;

	dc.SetFont(this->draw_command_line_font);

	dc.SetBrush(this->draw_command_line_cursor_color);
	dc.SetPen(this->draw_command_line_cursor_color);

	const wxPoint starting_position = (
		wxPoint(0, this->draw_command_line_text_help_get_starting_position().y) + this->draw_command_line_text_help_get_current_line_position(dc, this->draw_command_line_buffer_formated.size() - 1)
		) + wxPoint(
			dc.GetTextExtent(this->draw_command_line_buffer_formated[this->draw_command_line_buffer_formated.size() - 1]).x, 0
			);

	const wxSize cursor_size = (
		wxSize(dc.GetTextExtent("W").x, dc.GetTextExtent("W").y)
		); 

	if (
		this->draw_command_line_cursor_color.GetAlpha() == 0
		) return; 

	dc.DrawRectangle(starting_position, cursor_size);
}