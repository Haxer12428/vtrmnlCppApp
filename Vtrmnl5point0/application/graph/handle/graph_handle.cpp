#include "../graph.h"

const void graph::handle_limit_buffer()
{
	const size_t buffer_limit = this->GetClientSize().x / (this->buffer_draw_lenght + this->buffer_draw_spacing); 

	if (
		this->buffer.size() <= buffer_limit
		) return; 

	std::vector<int> limited_buffer; 
	const size_t buffer_difference = this->buffer.size() - buffer_limit; 

	for (
		size_t iterator = buffer_difference; iterator < this->buffer.size(); iterator++
		) {
		limited_buffer.push_back(
			this->buffer[iterator]
		);
	}

	this->buffer = limited_buffer;
}

const void graph::handle_update_buffer() {
	const int assigned_value_call_val = this->assigned_function(); 

	this->buffer.push_back(
		assigned_value_call_val
	);
	this->maximal_value = std::max(assigned_value_call_val, this->maximal_value);
}

const void graph::handle_buffer() {
	std::thread t([&] {
		do {
			std::this_thread::sleep_for(
				this->refresh_rate
			);

			this->handle_update_buffer();
			this->handle_limit_buffer();

			this->Refresh(); 
		} while (
			true
			);
		});
	t.detach();
}