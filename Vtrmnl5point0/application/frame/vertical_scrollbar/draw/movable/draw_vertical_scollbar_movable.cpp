#include "../../../frame.h"

const void frame::draw_vertical_scrollbar_movable(
	wxAutoBufferedPaintDC& paint
) {
	const wxPoint current_movable_position = this->draw_vertical_scrollbar_help_get_movable_current_position();
	const wxSize current_movable_size = this->draw_vertical_scrollbar_help_get_movable_size();

	paint.SetBrush(
		this->draw_vertical_scrollbar_movable_color
	);

	paint.SetPen(
		this->draw_vertical_scrollbar_movable_color
	);

	paint.DrawRoundedRectangle(
		wxRect(current_movable_position, current_movable_size), 1.5
	);
}