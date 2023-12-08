#include "../Render.h"

Render::Graph::Graph(
	const std::string& _NAME, const int& _SIZEX, const int& _SIZEY, const int& _MAXIMAL, const std::string &_UNIT
) : wxFrame(nullptr, wxID_ANY, _NAME, wxDefaultPosition, wxSize(_SIZEX, _SIZEY)), _UNIT(_UNIT), _NAME(_NAME) {
	this->SetBackgroundColour(*wxBLACK);

	this->ConfigureBinds();

	this->ConfigureMaximal(
		_MAXIMAL
	);

	this->RefreshBuffer();
}