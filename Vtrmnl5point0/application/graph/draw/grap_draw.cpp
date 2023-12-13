#include "../graph.h"

const void graph::draw_update_name() {
	if (
		this->buffer.size() == 0
		) return; 

	const int buffer_last_procentage = float(
		float(this->buffer[this->buffer.size() - 1]) / float(this->maximal_value))*100; 

	const std::string buffer_last_procentage_formated = " | " + std::to_string(buffer_last_procentage) + "%";
	this->SetTitle(this->name + buffer_last_procentage_formated);
}

void graph::draw(
	wxPaintEvent& evt
) {
	this->Freeze();

	wxAutoBufferedPaintDC paint = wxAutoBufferedPaintDC(this);

	this->draw_background(
		paint
	);
	this->draw_status_info(
		paint
	);
	this->draw_buffer(
		paint
	);
	this->draw_update_name();

	this->Thaw();

	evt.Skip(); 
}