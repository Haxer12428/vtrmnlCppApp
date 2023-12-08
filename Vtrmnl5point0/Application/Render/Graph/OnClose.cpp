#include "../Render.h"

void Render::Graph::DestroyOnClose(
	wxCloseEvent& evt
) {
	this->Hide();
}