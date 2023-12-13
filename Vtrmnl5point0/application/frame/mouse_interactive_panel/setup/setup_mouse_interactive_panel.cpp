#include "../../frame.h"

const void frame::setup_mouse_interactive_panel() {
	std::vector<int> mouse_interactive_panel_background_color = engine::vector::transform_string_vector_to_int_vector(
		engine::string(this->config->desire("$mouse_interactive_panel_background_color", "45,52,54")).get_vector());

	this->draw_mouse_interactive_panel_background_color = wxColor(
		mouse_interactive_panel_background_color[0], mouse_interactive_panel_background_color[1], mouse_interactive_panel_background_color[2]
	);

	int mouse_interactive_panel_reserved_space_user_extension = std::stoi(this->config->desire("$mouse_interactive_panel_reserved_space_user_extension", "0"));
	this->draw_mouse_interactive_panel_reserved_space_user_extension = mouse_interactive_panel_reserved_space_user_extension;

	std::vector<std::string> mouse_interactive_panel_font_info = engine::string(this->config->desire("$mouse_interactive_panel_font_info", "Hack,9")).get_vector();
	this->draw_mouse_interactive_panel_font_size = std::stoi(mouse_interactive_panel_font_info[1]);
	this->draw_mouse_interactive_panel_font_facename = mouse_interactive_panel_font_info[0];

	this->draw_mouse_interactive_panel_font = wxFont(
		this->draw_mouse_interactive_panel_font_size, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD
	); this->draw_mouse_interactive_panel_font.SetFaceName(this->draw_mouse_interactive_panel_font_facename);

	this->draw_mouse_interactive_panel_spacing_between_text = std::stoi(this->config->desire("$mouse_interactive_panel_spacing_between_text", "10"));

	this->draw_mouse_interactive_panel_text_user_push_x = std::stoi(this->config->desire("$mouse_interactive_panel_text_user_push_x", "10"));

	this->setup_mouse_interactive_panel_assigned_functions();
}