#include "../graph.h"

const void graph::draw_buffer(
	wxAutoBufferedPaintDC& paint
) { 
	const int buffer_timeframe_size_x = this->buffer_draw_lenght; 
	const wxSize buffer_draw_size = this->GetClientSize() - wxSize(0, this->status_info_reserved_space + 1);
	const wxPoint buffer_draw_starting_position = wxPoint(0, 0);

	size_t Iterator = 0;

	for (
		int buffer_timeframe_value : this->buffer
		) {

		const int buffer_timeframe_size_y = int(
			float(buffer_draw_size.y) * float(float(buffer_timeframe_value) / float(this->maximal_value))
			);

		const int buffer_position_y = int(
			buffer_draw_size.y - buffer_timeframe_size_y
			);

		const int buffer_position_x = int(
			buffer_draw_starting_position.x + (Iterator * (buffer_timeframe_size_x + this->buffer_draw_spacing))
			);

		const float buffer_factor_to_maximal_size = float(
			float(buffer_timeframe_value) / float(this->maximal_value)
			);

		const wxPoint buffer_position = wxPoint(
			buffer_position_x, buffer_position_y
		);

		const wxSize buffer_size = wxSize(
			buffer_timeframe_size_x, buffer_timeframe_size_y
		);

		wxColor buffer_color = this->buffer_color_default;

		const float medium_stage = .40; 
		const float high_stage = .75; 

		if (medium_stage <= buffer_factor_to_maximal_size && buffer_factor_to_maximal_size <= high_stage){
			buffer_color = this->buffer_color_medium; 
		} 

		if (high_stage <= buffer_factor_to_maximal_size) {
			buffer_color = this->buffer_color_high;
		}

		paint.SetPen(buffer_color); 
		paint.SetBrush(buffer_color);

		paint.DrawRectangle(
			buffer_position, buffer_size
		);

		Iterator++;
	}

}