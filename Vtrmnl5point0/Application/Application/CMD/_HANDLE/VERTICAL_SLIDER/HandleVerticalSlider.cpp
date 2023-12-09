#include "../../Cmd.h"

const int Cmd::VERTICAL_SLIDER_HANDLE_GET_MAX_SCROLL() {
	const int VERTICAL_SLIDER_MAIN_SIZE_Y = this->VERTICAL_SLIDER_DRAW_GET_MAIN_SIZE().y;
	const int VERTICAL_SLIDER_START_Y = this->VERTICAL_SLIDER_DRAW_GET_MAIN_STARTING_POSITION().y;
	const int VERTICAL_SLIDER_FINAL_Y = this->VERTICAL_SLIDER_DRAW_GET_MAIN_FINAL_POSITION().y;

	return (
		VERTICAL_SLIDER_FINAL_Y - VERTICAL_SLIDER_START_Y - VERTICAL_SLIDER_MAIN_SIZE_Y
	);
}

const void Cmd::VERTICAL_SLIDER_HANDLE_SET_SCROLL(
	const int& SCROLL
) {
	const int SCROLL_LIMITED = std::max(0, std::min(SCROLL, this->VERTICAL_SLIDER_HANDLE_GET_MAX_SCROLL())); 
	this->VERTICAL_SLIDER_SCROLL = SCROLL_LIMITED;
}

void Cmd::VERTICAL_SLIDER_HANLE_MOUSE_INTERACTION_START(
	wxMouseEvent& evt
) {
	wxPoint MOUSE_POSITION = evt.GetPosition();

	wxPoint VERTICAL_SLIDER_MAIN_POSITION = this->VERTICAL_SLIDER_DRAW_GET_MAIN_STARTING_POSITION();
	wxSize VERTICAL_SLIDER_MAIN_SIZE = this->VERTICAL_SLIDER_DRAW_GET_MAIN_SIZE();
	wxPoint VERTICAL_SLIDER_MAIN_FINAL_POSITION = this->VERTICAL_SLIDER_DRAW_GET_MAIN_FINAL_POSITION();

	if (
		!(VERTICAL_SLIDER_MAIN_POSITION.x <= MOUSE_POSITION.x && MOUSE_POSITION.x <= VERTICAL_SLIDER_MAIN_FINAL_POSITION.x && VERTICAL_SLIDER_MAIN_POSITION.y <= MOUSE_POSITION.y && MOUSE_POSITION.y <= VERTICAL_SLIDER_MAIN_FINAL_POSITION.y)
		) {
		evt.Skip(); return;
	}
	this->VERTICAL_SLIDER_MAIN_INTERACTING = true;
	this->VERTICAL_SLIDER_MAIN_DIFFERENCE_FROM_MOUSE_Y = MOUSE_POSITION.y - VERTICAL_SLIDER_MAIN_POSITION.y - this->VERTICAL_SLIDER_SCROLL; 
}

void Cmd::VERTICAL_SLIDER_HANDLE_MOUSE_INTERACTION(
	wxMouseEvent& evt
) {
	if (
		!evt.LeftIsDown()
		) {
		this->VERTICAL_SLIDER_MAIN_INTERACTING = false; evt.Skip(); return;
	}

	if (
		!this->VERTICAL_SLIDER_MAIN_INTERACTING
		) {
		evt.Skip(); return; 
	}

	wxPoint MOUSE_POSITION = evt.GetPosition(); 

	wxPoint VERTICAL_SLIDER_MAIN_POSITION = this->VERTICAL_SLIDER_DRAW_GET_MAIN_STARTING_POSITION();
	wxSize VERTICAL_SLIDER_MAIN_SIZE = this->VERTICAL_SLIDER_DRAW_GET_MAIN_SIZE();
	wxPoint VERTICAL_SLIDER_MAIN_FINAL_POSITION = this->VERTICAL_SLIDER_DRAW_GET_MAIN_FINAL_POSITION();

	const int MOUSE_DIFFERENCE = this->VERTICAL_SLIDER_MAIN_DIFFERENCE_FROM_MOUSE_Y;
	const int VERTICAL_SLIDER_SCROLL_CALCULATED = (MOUSE_POSITION.y - this->VERTICAL_SLIDER_DRAW_GET_MAIN_STARTING_POSITION().y) - MOUSE_DIFFERENCE;

	if (
		VERTICAL_SLIDER_SCROLL_CALCULATED == this->VERTICAL_SLIDER_SCROLL
		) {
		evt.Skip(); return; 
	}

	
	this->VERTICAL_SLIDER_HANDLE_SET_SCROLL(VERTICAL_SLIDER_SCROLL_CALCULATED); 
	this->FORCE_UPDATE = true;
}

void Cmd::VERTICAL_SLIDER_HANDLE_MOUSEWHEEL_INTERACTION(
	wxMouseEvent& evt
) {
	int ROTATION = evt.GetWheelRotation() / evt.GetWheelDelta(); 

	this->VERTICAL_SLIDER_HANDLE_SET_SCROLL(
		this->VERTICAL_SLIDER_SCROLL - ROTATION*50
	);
	
	this->FORCE_UPDATE = true; evt.Skip();
}

const float Cmd::VERTICAL_SLIDER_HANDLE_GET_SCROLL_PROCENTAGE() {
	const int MAX_SCROLL = this->VERTICAL_SLIDER_HANDLE_GET_MAX_SCROLL();
	const int SCROLL = this->VERTICAL_SLIDER_SCROLL;

	return float(float(SCROLL) / float(MAX_SCROLL));
}