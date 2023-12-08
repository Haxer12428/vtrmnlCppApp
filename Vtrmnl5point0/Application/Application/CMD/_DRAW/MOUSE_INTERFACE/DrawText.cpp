#include "../../Cmd.h"

const std::vector<std::string> Cmd::MOUSE_INTERFACE_DRAW_GET_TEXT_VECTOR() {
	return { "(~) ", " Settings ", " Memory Usage ", " Help "};
}

const void Cmd::MOUSE_INTERFACE_DRAW_UPDATE_TEXT_SIZES(
	wxPaintDC* dc 
) {
	std::vector<int> _TEXT_SIZES; 

	for (
		std::string _TEXT : this->MOUSE_INTERFACE_DRAW_GET_TEXT_VECTOR()
		) {
		_TEXT_SIZES.push_back(dc->GetTextExtent(_TEXT).x);
	} this->MOUSE_INTERFACE_TEXT_SIZES = _TEXT_SIZES;
}

const std::string Cmd::MOUSE_INTERFACE_DRAW_GET_TEXT() {
	const std::vector<std::string> _VEC = this->MOUSE_INTERFACE_DRAW_GET_TEXT_VECTOR(); 
	std::string _STR = ""; 

	for (
		std::string _STRiterator : _VEC 
		) {
		_STR += _STRiterator; 
	}

	return _STR; 
}

const wxPoint Cmd::MOUSE_INTERFACE_DRAW_GET_TEXT_POSITION(
	wxPaintDC *dc, const std::string &TEXT
) {
	return wxPoint(
		this->MOUSE_INTERFACE_ADDITIONAL_TEXT_X, (this->MOUSE_INTERFACE_RESERVED_SPACE / 2) - dc->GetTextExtent(TEXT).y / 2
	);
}

const void Cmd::MOUSE_INTERFACE_DRAW_SETUP_TEXT_DC(
	wxPaintDC *dc
) {
	wxFont _FONT = wxFont(
		this->MOUSE_INTERFACE_FONT_SIZE, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD
	); _FONT.SetFaceName(this->MOUSE_INTERFACE_FONT_FACENAME);

	dc->SetFont(_FONT);

	dc->SetTextForeground(this->MOUSE_INTERFACE_COLOR_TEXT);
}

const void Cmd::MOUSE_INTERFACE_DRAW_TEXT(
	wxPaintDC *dc
) {
	const std::string _TEXT = this->MOUSE_INTERFACE_DRAW_GET_TEXT();

	dc->DrawText(
		_TEXT, this->MOUSE_INTERFACE_DRAW_GET_TEXT_POSITION(dc, _TEXT)
	);
}