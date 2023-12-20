#include "../../frame.h"

void frame::handle_command_line_cursor_pulse() {
	std::thread d_thread([&]
		{
			do {
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

				const int alpha = this->draw_command_line_cursor_color.GetAlpha();


				if (
					alpha != 0
					) {
					this->draw_command_line_cursor_color = wxColor(
						this->draw_command_line_cursor_color.GetRed(), this->draw_command_line_cursor_color.GetGreen(), this->draw_command_line_cursor_color.GetBlue(), 0
					);
				}
				else {
					this->draw_command_line_cursor_color = wxColor(
						this->draw_command_line_cursor_color.GetRed(), this->draw_command_line_cursor_color.GetGreen(), this->draw_command_line_cursor_color.GetBlue(), 255
					);
				}

				this->Refresh();
			} while (
				true
				);
		});

	d_thread.detach();
}