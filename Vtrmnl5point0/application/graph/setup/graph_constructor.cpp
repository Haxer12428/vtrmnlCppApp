#include "../graph.h"

graph::graph(
	wxFrame* parent, const std::string& name, const int &maximal_value, const std::string& unit
) : wxFrame(parent, wxID_ANY, name), maximal_value(maximal_value), unit(unit)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	this->setup_binds();
	this->handle_buffer();

	this->Show(); 
}