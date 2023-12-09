#include "../../Cmd.h"

const void Cmd::COMMAND_LINE_HANDLE_PUSH_BUFFER_LINE(
	const std::string& BUFFER
) {
	std::string BUFFER_CUT = BUFFER; 

	do {
		std::string BUFFER_CUT_CURRENT = BUFFER_CUT;
		size_t FOUND_NEW_LINE = Engine::String::Find(BUFFER_CUT, "\n");

		if (
			FOUND_NEW_LINE == -1 
			) { 
			this->COMMAND_LINE_ORIGINAL_BUFFER.push_back(BUFFER_CUT); break; 
		}

		BUFFER_CUT_CURRENT.resize(FOUND_NEW_LINE);
		this->COMMAND_LINE_ORIGINAL_BUFFER.push_back(BUFFER_CUT_CURRENT);

		BUFFER_CUT = BUFFER_CUT.substr(FOUND_NEW_LINE + 2);
	} while (
		true
		); 
	this->FORCE_UPDATE = true; 
}

const std::vector<std::string> Cmd::COMMAND_LINE_HANDLE_FORMAT_BUFFER(
	wxPaintDC* dc, const std::vector<std::string>& BUFFER, const int& MAXIMAL_X
) {
	std::vector<std::string> FORMATED_BUFFER = BUFFER; 

	do {
		std::vector<std::string> FORMATING_CACHE = {};

		bool MADE_CHANGES = false; 

		for (
			std::string ORIGINAL_LINE : FORMATED_BUFFER
			) {
			std::string ORIGINAL_LINE_CUT = ORIGINAL_LINE;

			bool MADE_CHANGES_THIS_LINE = false; 

			do {
				if (
					dc->GetTextExtent(ORIGINAL_LINE_CUT).x <= MAXIMAL_X
					) {
					FORMATING_CACHE.push_back(ORIGINAL_LINE_CUT); 

					if (
						MADE_CHANGES_THIS_LINE
						) FORMATING_CACHE.push_back(ORIGINAL_LINE.substr(ORIGINAL_LINE_CUT.length()));
					
					break;
				}

				MADE_CHANGES = true; MADE_CHANGES_THIS_LINE = true;
				ORIGINAL_LINE_CUT.resize(ORIGINAL_LINE_CUT.length() - 1);
			} while (
				true
				);
		}
		FORMATED_BUFFER = FORMATING_CACHE;

		if (
			!MADE_CHANGES
			) {
			return FORMATED_BUFFER;
		}
	} while (
		true
		);
}