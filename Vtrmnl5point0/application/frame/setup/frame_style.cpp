#include "../frame.h"

const void frame::setup_style() {
	const std::vector<int> frame_size = engine::vector::transform_string_vector_to_int_vector(
		engine::string(this->config->desire("$frame_size", "1200,850")).get_vector()
	);

	this->SetSize(wxSize(
		frame_size[0], frame_size[1]
	));
}