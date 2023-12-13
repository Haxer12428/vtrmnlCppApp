#include "../../frame.h"

const void frame::draw_vertical_scrollbar(
	wxAutoBufferedPaintDC& dc
) {
	this->draw_vertical_scrollbar_background(dc);
}