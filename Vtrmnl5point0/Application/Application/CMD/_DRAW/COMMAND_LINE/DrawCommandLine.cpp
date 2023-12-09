#include "../../Cmd.h"

void Cmd::COMMAND_LINE_DRAW(
	wxPaintEvent& evt
) {
	wxPaintDC* dc = new wxPaintDC(this);

	this->COMMAND_LINE_DRAW_BUFFER_SETUP_DC(dc);
	this->COMMAND_LINE_FORMATED_BUFFER = this->COMMAND_LINE_HANDLE_FORMAT_BUFFER(dc, this->COMMAND_LINE_ORIGINAL_BUFFER, this->COMMAND_LINE_DRAW_GET_SIZE().x);

	this->COMMAND_LINE_DRAW_BUFFER(dc);

	delete dc; evt.Skip();
}