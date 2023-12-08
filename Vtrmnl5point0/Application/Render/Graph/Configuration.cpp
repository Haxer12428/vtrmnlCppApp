#include "../Render.h"

void Render::Graph::ConfigureBinds() {
	this->Bind(wxEVT_PAINT, &Render::Graph::RenderGraph, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &Render::Graph::DestroyOnClose, this);
}



void Render::Graph::ConfigureMaximal(
	const int& _MAX
) {
	if (
		_MAX == -1
		) {
		this->_MAXIMAL = 0; this->_LOCKED = false; return; 
	}
	this->_MAXIMAL = _MAX; this->_LOCKED = true; 
}