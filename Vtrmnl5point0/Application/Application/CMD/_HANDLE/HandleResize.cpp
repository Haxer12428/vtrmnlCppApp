#include "../Cmd.h"

void Cmd::HANDLE_RESIZE(
	wxSizeEvent& evt
) {
	this->Refresh(); this->Update();
}