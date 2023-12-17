#include "../../frame.h"

const void frame::setup_command_line() {
	std::vector<std::string> command_line_font_info = engine::string(
		this->config->desire("$command_line_font_info", "Hack,10")
	).get_vector();

	this->draw_command_line_font_facename = command_line_font_info[0];
	this->draw_command_line_font_size = std::stoi(command_line_font_info[1]);

	this->draw_command_line_font = wxFont(
		this->draw_command_line_font_size, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD
	); this->draw_command_line_font.SetFaceName(this->draw_command_line_font_facename);
	
	std::vector<int> command_line_text_push = engine::vector::transform_string_vector_to_int_vector(engine::string(
		this->config->desire("$command_line_text_push", "10,5")
	).get_vector());

	this->draw_command_line_text_push_x = command_line_text_push[0];
	this->draw_command_line_text_push_y = command_line_text_push[1];

	this->draw_command_line_text_spacing = std::stoi(this->config->desire("$draw_command_line_text_spacing", "10"));

	this->setup_command_line_assigned_functions();
}