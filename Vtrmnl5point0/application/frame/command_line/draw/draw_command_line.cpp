#include "../../frame.h"

const void frame::draw_command_line(
	wxAutoBufferedPaintDC& dc
) {
	this->draw_command_line_cursor(dc);
	this->draw_command_line_text(dc);
}