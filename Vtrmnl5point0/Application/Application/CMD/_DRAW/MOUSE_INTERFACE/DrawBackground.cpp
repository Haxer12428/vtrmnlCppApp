#include "../../Cmd.h"

const wxSize Cmd::MOUSE_INTERFACE_DRAW_GET_BACKGROUND_SIZE() {
	return wxSize(this->GetClientSize().x, this->MOUSE_INTERFACE_RESERVED_SPACE);
}

const wxPoint Cmd::MOUSE_INTERFACE_DRAW_GET_BACKGROUND_POSITION() {
	return wxPoint(0, 0);
}

const void Cmd::MOUSE_INTERFACE_DRAW_BACKGROUND(
	wxPaintDC* dc
) {
	dc->SetBrush(this->MOUSE_INTERFACE_COLOR_BACKGROUND);
	dc->SetPen(this->MOUSE_INTERFACE_COLOR_BACKGROUND);

	dc->DrawRectangle(
		this->MOUSE_INTERFACE_DRAW_GET_BACKGROUND_POSITION(), this->MOUSE_INTERFACE_DRAW_GET_BACKGROUND_SIZE()
	);
}