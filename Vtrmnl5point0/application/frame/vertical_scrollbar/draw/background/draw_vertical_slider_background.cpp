#include "../../../frame.h"

const void frame::draw_vertical_scrollbar_background(
	wxAutoBufferedPaintDC& paint
) {
	paint.SetBrush(this->draw_vertical_scrollbar_background_color);
	paint.SetPen(this->draw_vertical_scrollbar_background_color);

	paint.DrawRectangle(
		this->draw_vertical_scrollbar_help_get_background_starting_position(), this->draw_vertical_scrollbar_help_get_background_size()
	);
}