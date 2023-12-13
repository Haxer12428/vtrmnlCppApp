#include "../frame.h"

void frame::handle_resize(
	wxSizeEvent& evt
) {
	this->Refresh();
	evt.Skip(); 
}