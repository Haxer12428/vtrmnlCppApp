#include "../frame.h"

const void frame::setup_binds() {
	this->Bind(wxEVT_PAINT, &frame::draw, this);
	this->Bind(wxEVT_LEFT_DOWN, &frame::handle_mouse_interactive_panel_interaction, this);
	this->Bind(wxEVT_SIZE, &frame::handle_resize, this);
	this->Bind(wxEVT_LEFT_DOWN, &frame::handle_vertical_scrollbar_interaction_start, this);
	this->Bind(wxEVT_MOTION, &frame::handle_vertical_scrollbar_interaction, this);
	this->Bind(wxEVT_SIZE, &frame::handle_vertical_scrollbar_resize, this);
	this->Bind(wxEVT_IDLE, &frame::handle_resize_after, this);
	this->Bind(wxEVT_CHAR, &frame::handle_command_line_buffer_input, this);
}