#include "../frame.h"

void frame::draw(
	wxPaintEvent& evt
) {
	wxAutoBufferedPaintDC paint(this);

	this->frame_draw_background(paint); 
	this->draw_mouse_interactive_panel_main(paint);
	this->draw_vertical_scrollbar(paint);

}