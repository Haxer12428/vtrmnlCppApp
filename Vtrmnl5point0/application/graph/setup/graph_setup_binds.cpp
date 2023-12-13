#include "../graph.h"

void graph::setup_binds() {
	this->Bind(wxEVT_PAINT, &graph::draw, this);
}