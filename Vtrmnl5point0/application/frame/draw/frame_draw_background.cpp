#include "../frame.h"

const void frame::frame_draw_background(
	wxAutoBufferedPaintDC& paint
) {

	const wxPoint background_starting_position = wxPoint(0, 0);
	const wxSize background_size = this->GetClientSize();

	paint.SetBrush(this->frame_draw_background_color);
	paint.SetPen(this->frame_draw_background_color);

	paint.DrawRectangle(
		background_starting_position, background_size
	);
}