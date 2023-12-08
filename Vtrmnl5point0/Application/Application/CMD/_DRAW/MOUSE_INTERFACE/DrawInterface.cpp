#include "../../Cmd.h"

void Cmd::MOUSE_INTERFACE_DRAW(
	wxPaintEvent& evt
) {
	this->MOUSE_INTERFACE_DRAW_DC = new wxPaintDC(this);
	wxPaintDC* dc = this->MOUSE_INTERFACE_DRAW_DC;

	this->MOUSE_INTERFACE_DRAW_SETUP_TEXT_DC(dc);
	this->MOUSE_INTERFACE_DRAW_UPDATE_TEXT_SIZES(dc);

	this->SETUP_MOUSE_INTERFACE_RESERVED_SPACE(dc->GetTextExtent(this->MOUSE_INTERFACE_DRAW_GET_TEXT()).y);

	this->MOUSE_INTERFACE_DRAW_BACKGROUND(dc);
	this->MOUSE_INTERFACE_DRAW_TEXT(dc);

	evt.Skip();
}
