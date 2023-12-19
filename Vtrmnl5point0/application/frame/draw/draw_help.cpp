#include "../frame.h"

const wxColor frame::draw_help_color_hex_to_rgb(
	const std::string& hex_clr_str 
) const {
	std::string hex_clr_str_remaining = hex_clr_str;
	unsigned int r, g, b; 

	const std::string r_hex = (
		std::string(1, hex_clr_str[0]) + std::string(1, hex_clr_str[1])
		);

	const std::string g_hex = (
		std::string(1, hex_clr_str[2]) + std::string(1, hex_clr_str[3])
		);

	const std::string b_hex = (
		std::string(1, hex_clr_str[4]) + std::string(1, hex_clr_str[5])
		);

	std::stringstream ss_r; 
	ss_r << std::hex << r_hex;
	ss_r >> r;
	r = r * (255 / 12);

	std::stringstream ss_g;
	ss_g << std::hex << g_hex;
	ss_g >> g;
	g = g * (255 / 12);

	std::stringstream ss_b;
	ss_b << std::hex << b_hex;
	ss_b >> b;
	b = b * (255 / 12);


	return wxColor(
		r, g, b
	);
}