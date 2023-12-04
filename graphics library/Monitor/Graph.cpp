#include "Graph.h"

Graph::Graph(
	const wxString& Name, const int MAXIMAL_SIZE = -1
) : wxFrame(nullptr, wxID_ANY, Name, wxDefaultPosition, wxSize(600, 300)), Name(Name) {
	this->ConfigureBinds();
	this->UpdateBuffer();
	this->SetBackgroundColour(*wxBLACK);

	if (
		MAXIMAL_SIZE != -1
		) {
		this->MaximalValueSeen = MAXIMAL_SIZE; this->MaximalValueSeenLocked = true; 
	}

	this->Show(true);
}

void Graph::ConfigureBinds()
{
	this->Bind(wxEVT_PAINT, &Graph::RenderGraph, this);
}