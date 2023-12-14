#include "../../frame.h"

void frame::handle_vertical_scrollbar_resize(
	wxSizeEvent& evt
) {
	const int maximal_scroll = this->draw_vertical_scollbar_help_get_maximal_scroll(); 

	this->draw_vertical_scrollbar_movable_scroll_amount = std::max(0,
		std::min(this->draw_vertical_scrollbar_movable_scroll_amount, maximal_scroll)
	); evt.Skip(); 
}