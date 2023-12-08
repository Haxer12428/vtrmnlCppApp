#include "../../Cmd.h"

void Cmd::MOUSE_HANDLE_SET_POSITION(
	wxMouseEvent& evt
) {
	this->MOUSE_POSITION = evt.GetPosition(); evt.Skip();
}