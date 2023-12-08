#include "../Cmd.h"

const void Cmd::SETUP_BACKGROUND_STYLE(
	const int& r, const int& g, const int& b
) {
	this->SetBackgroundColour(wxColor(r, g, b));
}