#include "../frame.h"

void frame::handle_resize_after(
	wxIdleEvent& evt
) {
	if (
		this->handle_resize_after_resizing
		) {
		this->handle_resize_after_resizing = false;
		this->handle_command_line_buffer_format(this->draw_command_line_buffer_original, this->draw_command_line_text_help_get_area_size().x);
		//wxLogMessage("fin");

		this->Refresh();
	}
}

void frame::handle_resize(
	wxSizeEvent& evt
) {
	this->handle_resize_after_resizing = true; 


	this->Refresh();
	evt.Skip(); 
}