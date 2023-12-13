#include "../../frame.h"

const void frame::setup_vertical_scrollbar() {
	this->draw_vertical_scrollbar_background_reserved_space = std::stoi(
		this->config->desire("$draw_vertical_scrollbar_background_reserved_space", "20"));

	this->draw_vertical_scrollbar_movable_area_dif = std::stoi(
		this->config->desire("$draw_vertical_scrollbar_movable_area_dif", "6")
	);

	const std::vector<int> draw_vertical_scrollbar_background_color_vec = engine::vector::transform_string_vector_to_int_vector(
		engine::string(this->config->desire("$draw_vertical_scrollbar_background_color", "43,48,50")).get_vector()
	);

	this->draw_vertical_scrollbar_background_color = wxColor(
		draw_vertical_scrollbar_background_color_vec[0], draw_vertical_scrollbar_background_color_vec[1], draw_vertical_scrollbar_background_color_vec[2]
	);

	const std::vector<int> draw_vertical_scrollbar_movable_color_vec = engine::vector::transform_string_vector_to_int_vector(
		engine::string(this->config->desire("$draw_vertical_scrollbar_movable_color", "163,166,165")).get_vector()
	);

	this->draw_vertical_scrollbar_movable_color = wxColor(
		draw_vertical_scrollbar_movable_color_vec[0], draw_vertical_scrollbar_movable_color_vec[1], draw_vertical_scrollbar_movable_color_vec[2]
	);
}