#include "../frame.h"

const void frame::setup_frame_draw_background_color() {
	const std::vector<int> frame_background_color = engine::vector::transform_string_vector_to_int_vector(
		engine::string(this->config->desire("$frame_background_color", "35,39,41")).get_vector());

	this->frame_draw_background_color = wxColor(
		frame_background_color[0], frame_background_color[1], frame_background_color[2]
	);
}