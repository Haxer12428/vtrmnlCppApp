#include "../graph.h"

const void graph::draw_background(
	wxAutoBufferedPaintDC& paint
) {

	const wxSize background_size = this->GetClientSize(); 
	const wxPoint background_starting_position = wxPoint(0, 0);

	const wxColor background_color = wxColor(0, 0, 0);

	paint.SetPen(background_color);
	paint.SetBrush(background_color);

	paint.DrawRectangle(
		background_starting_position, background_size
	);
}