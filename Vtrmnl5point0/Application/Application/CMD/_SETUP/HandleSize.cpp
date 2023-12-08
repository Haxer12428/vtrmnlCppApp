#include "../Cmd.h"

const void Cmd::SETUP_SIZE(
	const int& DEFAULT_X, const int& DEFAULT_Y
) {
	this->SetSize(wxSize(
		DEFAULT_X, DEFAULT_Y
	));
}