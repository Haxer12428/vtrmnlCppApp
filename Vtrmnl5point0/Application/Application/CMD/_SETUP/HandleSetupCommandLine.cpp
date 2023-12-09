#include "../Cmd.h"

const void Cmd::SETUP_COMMAND_LINE_FONT(
	const std::string& FACENAME, const int& SIZE
) {
	this->COMMAND_LINE_FONT_FACENAME = FACENAME; 
	this->COMMAND_LINE_FONT_SIZE = SIZE; 
}

const void Cmd::SETUP_COMMAND_LINE_DEFAULT_COLOR(
	const int& R, const int& G, const int& B
) {
	this->COMMAND_LINE_DEFAULT_COLOR = wxColor(R, G, B);
}

const void Cmd::SETUP_COMMAND_LINE_DIFFERENCE_BETWEEN_LINES(
	const int& DIF
) {
	this->COMMAND_LINE_DIFFERENCE_BETWEEN_LINES = DIF;
}

const void Cmd::SETUP_COMMAND_LINE_DIFFERENCE_BETWEEN_EDGES(
	const int& LENGHT, const int& HEIGHT
) {
	this->COMMAND_LINE_DIFFERENCE_BETWEEN_EDGES = wxPoint(LENGHT, HEIGHT);
}