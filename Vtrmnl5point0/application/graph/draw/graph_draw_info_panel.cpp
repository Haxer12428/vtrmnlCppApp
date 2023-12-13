#include "../graph.h"

const void graph::draw_status_info(
	wxAutoBufferedPaintDC& paint
) {
	if (
		this->buffer.size() == 0
		) return; 

	//colors 
	paint.SetBrush(this->status_info_color);
	paint.SetPen(wxPen(this->status_info_color));
	paint.SetTextForeground(this->status_info_color);

	wxFont text_font = wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	text_font.SetFaceName("Hack");

	paint.SetFont(text_font);

	//...
	const wxSize window_size = this->GetClientSize();

	const wxPoint draw_status_info_line_starting_position = wxPoint(
		0, window_size.y - this->status_info_reserved_space
		);

	const wxPoint draw_status_info_line_final_position = (
		draw_status_info_line_starting_position + wxPoint(window_size.x, 0)
		);

	const std::string text = "Current: " + std::to_string(this->buffer[this->buffer.size() - 1]) + this->unit + " | Min: " + std::to_string(this->get_minimal_buffer()) + this->unit + " | Avg: " + std::to_string(this->get_average_buffer()) + this->unit + " | Max: " + std::to_string(this->get_maximal_buffer()) + this->unit;

	const wxSize text_size = paint.GetTextExtent(text);

	const wxPoint draw_status_info_text_starting_position = wxPoint(
		window_size.x/2 - text_size.x/2, window_size.y - this->status_info_reserved_space/2 - text_size.y/2
	);

	paint.DrawLine(
		draw_status_info_line_starting_position, draw_status_info_line_final_position
	);

	paint.DrawText(
		text, draw_status_info_text_starting_position
	);
}