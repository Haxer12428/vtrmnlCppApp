#include "../../Cmd.h"

void Cmd::VERTICAL_SLIDER_DRAW(
	wxPaintEvent& evt 
) { 
	wxPaintDC* dc = new wxPaintDC(this);
	
	this->VERTICAL_SLIDER_DRAW_BACKGROUND(dc);
	this->VERTICAL_SLIDER_DRAW_MAIN(dc);

	delete dc;
	evt.Skip();
}