#include "../../frame.h"

const std::vector<std::string> frame::handle_command_line_buffer_input_help_get_arguments(
	const std::string& input
) const {
	std::vector<std::string> arguments; 

	// determinating assigned_function name 
	std::string input_cut = input;

	while (
		true
		) {
		size_t found_at = engine::string(input_cut).find_phrase(" ");

		if (
			found_at == std::string::npos
			) {
			return {
				input_cut
			};
		}

		if (
			found_at != 0
			) {
			std::string input_cut_cache = input_cut;
			input_cut_cache.resize(found_at);

			arguments.push_back(
				input_cut_cache
			); break; 
		}

		input_cut = input_cut.substr(found_at + 1); 
	}

	// deteminating arguments 

	do {
		size_t arg_found_at = engine::string(input_cut).find_phrase("-");

		// argument char not found || exit 
		if (
			arg_found_at == std::string::npos
			) break; 

		input_cut = input_cut.substr(arg_found_at + 1); 

		size_t arg_found_at_end = engine::string(input_cut).find_phrase(" ");
	
		// space not found || push & exit 
		if (
			arg_found_at_end == std::string::npos
			) {
			arguments.push_back(
				input_cut
			); break; 
		}
		
		// push && proceed to next 
		std::string input_cut_cache = input_cut;
		input_cut_cache.resize(arg_found_at_end);

		arguments.push_back(
			input_cut_cache
		);
	} while (
		true
		);

	return arguments;	 
}

const void frame::handle_command_line_buffer_input_awake_assigned_function(
	const std::string& input
) {
	const std::vector<std::string> arguments = this->handle_command_line_buffer_input_help_get_arguments(input);

	if ( // empty string? 
		arguments.size() == 0
		) {
		return; 
	}


	// reformat args 
	std::vector<std::string> arguments_reformated;
	
	for (
		size_t iterator = 1; iterator < arguments.size(); iterator++
		) {
		arguments_reformated.push_back(arguments[iterator]);
	}

	// f_call
	const bool f_call_response = this->assigned_function_find_and_call(
		arguments[0], arguments_reformated
	);

	if (
		f_call_response
		) return; 

	this->handle_command_line_buffer_push_line(" \aFF0000error: \aFFFFFFFailed to find|call assigned function with given name.");
}

void frame::handle_command_line_buffer_input(
	wxKeyEvent& evt
) {
	const int key_code = evt.GetKeyCode();
	const std::string key_char = std::string(1, char(key_code));

	if (
		this->handle_command_line_buffer_input_mode == frame::command_line_buffer_input_mode::write
		) {
		if ( // windows key | skip
			key_code == WXK_WINDOWS_LEFT || key_code == WXK_WINDOWS_RIGHT
			) return; 

		if (
			key_code == WXK_RETURN || key_code == WXK_NUMPAD_ENTER 
			) {
			this->handle_command_line_buffer_input_awake_assigned_function(this->handle_command_line_buffer_input_cache);
			this->handle_command_line_buffer_input_cache.resize(0);

			this->handle_command_line_buffer_push_line("");
			this->handle_command_line_buffer_format(this->draw_command_line_buffer_original, this->draw_command_line_text_help_get_area_size().x);


			this->draw_command_line_cursor_position_in_buffer[0] = this->draw_command_line_buffer_formated.size() - 1;

			this->draw_vertical_scrollbar_movable_scroll_amount = this->draw_vertical_scollbar_help_get_maximal_scroll();
			this->Refresh();
			return; 
		}

		if (
			this->draw_command_line_buffer_original.size() == 0
			) {
			this->handle_command_line_buffer_push_line(""); 

		}

		if (
			key_code == WXK_BACK
			) {
			//decrement 

			if (
				this->draw_command_line_buffer_original[
					this->draw_command_line_buffer_original.size() - 1
				].length() != 0
				) 
			{
				this->draw_command_line_buffer_original[
					this->draw_command_line_buffer_original.size() - 1
				].resize(
					this->draw_command_line_buffer_original[this->draw_command_line_buffer_original.size() - 1].length() - 1
				);

				//this->draw_command_line_cursor_position_in_buffer[1] = this->draw_command_line_buffer_original[this->draw_command_line_buffer_original.size() - 1].length();
			}

			if (
				this->handle_command_line_buffer_input_cache.length() != 0
				) 
			{
				this->handle_command_line_buffer_input_cache.resize(
					this->handle_command_line_buffer_input_cache.length() - 1
				);
			}

			this->draw_vertical_scrollbar_movable_scroll_amount = this->draw_vertical_scollbar_help_get_maximal_scroll();
			this->handle_command_line_buffer_format(this->draw_command_line_buffer_original, this->draw_command_line_text_help_get_area_size().x);

			this->draw_command_line_cursor_position_in_buffer[1] = this->draw_command_line_buffer_formated[this->draw_command_line_buffer_formated.size() - 1].length();
			this->Refresh();
			return; 
		}


		//increment 
		this->draw_command_line_buffer_original[
			this->draw_command_line_buffer_original.size() - 1
		] += (
			key_char
			);

		this->handle_command_line_buffer_input_cache += (
			key_char
			);

		this->handle_command_line_buffer_format(this->draw_command_line_buffer_original, this->draw_command_line_text_help_get_area_size().x);
		this->draw_vertical_scrollbar_movable_scroll_amount = this->draw_vertical_scollbar_help_get_maximal_scroll();
		
		this->Refresh();;

		this->draw_command_line_cursor_position_in_buffer[1] = this->draw_command_line_buffer_formated[this->draw_command_line_buffer_formated.size() - 1].length();
		return; 
	}

	evt.Skip();
}