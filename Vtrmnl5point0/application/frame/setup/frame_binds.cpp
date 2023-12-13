#include "../frame.h"

const void frame::setup_binds() {
	this->Bind(wxEVT_PAINT, &frame::draw, this);
	this->Bind(wxEVT_LEFT_DOWN, &frame::handle_mouse_interactive_panel_interaction, this);
	this->Bind(wxEVT_SIZE, &frame::handle_resize, this);
}