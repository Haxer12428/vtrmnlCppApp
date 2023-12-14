#include "../frame.h"

const void frame::setup_config() {
	this->setup_frame_draw_background_color();
	this->setup_mouse_interactive_panel();
	this->setup_vertical_scrollbar();
	this->setup_command_line();
	this->setup_style();
}