#include "../../../frame.h"

const void frame::draw_command_line_text(
	wxAutoBufferedPaintDC& paint
) {
	paint.SetTextForeground(
		wxColor(255, 255, 255)
	);

	paint.SetFont(
		this->draw_command_line_font
	);

	const wxPoint command_line_size = this->draw_command_line_text_help_get_final_position() - this->draw_command_line_text_help_get_starting_position();

	paint.SetClippingRegion(
		this->draw_command_line_text_help_get_starting_position(), wxSize(command_line_size.x, command_line_size.y)
	);

	const int command_line_text_height = this->draw_command_line_text_help_get_text_line_height(paint);

	const int max_scroll = (
		this->draw_command_line_buffer_formated.size() * command_line_text_height
		) - command_line_size.y;

	int iterator_max = this->draw_command_line_buffer_formated.size(); 
	int iterator_min = 0;

	const int scroll_page_lines = command_line_size.y / command_line_text_height;

	const int scroll_amount = float(max_scroll) * this->draw_vertical_scrollbar_help_get_movable_scroll_procentage();

	if (
		0 < max_scroll
		) {
		iterator_min = std::max(0, std::min(int(this->draw_command_line_buffer_formated.size()), scroll_amount / command_line_text_height - 2));
		iterator_max = std::min(int(this->draw_command_line_buffer_formated.size()), iterator_min + scroll_page_lines + 4);
	}

	for (
		int iterator = iterator_min; iterator < iterator_max; iterator++
		) {
		const std::string text_line = this->draw_command_line_buffer_formated[
			iterator
		];

		const wxPoint text_line_position = this->draw_command_line_text_help_get_current_line_position(
			paint, iterator
		) + wxPoint(0, this->draw_command_line_text_help_get_starting_position().y);

		paint.DrawText(
			text_line, text_line_position
		);
	}
	
	paint.DestroyClippingRegion();
}