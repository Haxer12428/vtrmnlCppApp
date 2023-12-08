#include "../Cmd.h"

const void Cmd::SETUP_BINDS() {
	this->Bind(wxEVT_PAINT, &Cmd::MOUSE_INTERFACE_DRAW, this);
	this->Bind(wxEVT_LEFT_DOWN, &Cmd::MOUSE_INTERFACE_HANDLE_MOUSE_INTERACTION_OPEN, this);
	this->Bind(wxEVT_MOTION, &Cmd::MOUSE_HANDLE_SET_POSITION, this);
	this->Bind(wxEVT_PAINT, &Cmd::VERTICAL_SLIDER_DRAW, this);
	this->Bind(wxEVT_MOTION, &Cmd::VERTICAL_SLIDER_HANDLE_MOUSE_INTERACTION, this);
	this->Bind(wxEVT_LEFT_DOWN, &Cmd::VERTICAL_SLIDER_HANLE_MOUSE_INTERACTION_START, this);
	this->Bind(wxEVT_SIZE, &Cmd::HANDLE_RESIZE, this);
}