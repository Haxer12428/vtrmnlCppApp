#include "../../Cmd.h"

void Cmd::MOUSE_INTERFACE_HANDLE_MOUSE_INTERACTION_OPEN(
	wxMouseEvent& evt
) {
	const std::vector<std::string> _TEXT = this->MOUSE_INTERFACE_DRAW_GET_TEXT_VECTOR();
	const wxPoint _START = wxPoint(this->MOUSE_INTERFACE_ADDITIONAL_TEXT_X, 0);
	int _START_FROM_X = 0;

	for (
		size_t Iterator = 0; Iterator < _TEXT.size(); Iterator++
		) {
		std::string _TEXT_CURRENT = _TEXT[Iterator];

		wxPoint _START_CURRENT = _START + wxPoint(_START_FROM_X, 0);
		wxPoint _END_CURRENT = _START_CURRENT + wxPoint(this->MOUSE_INTERFACE_TEXT_SIZES[Iterator], this->MOUSE_INTERFACE_RESERVED_SPACE);

		//wxLogMessage(std::to_string(_START_FROM_X).c_str());
		if (
			_START_CURRENT.x <= this->MOUSE_POSITION.x && this->MOUSE_POSITION.x <= _END_CURRENT.x && _START_CURRENT.y <= this->MOUSE_POSITION.y && this->MOUSE_POSITION.y <= _END_CURRENT.y
			) {
			this->COMMANDS_HANDLE_FIND_AND_CALL(
				_TEXT_CURRENT, this->ARGUMENT_EMPTY
			);
		}

		_START_FROM_X += this->MOUSE_INTERFACE_TEXT_SIZES[Iterator];
	}
}