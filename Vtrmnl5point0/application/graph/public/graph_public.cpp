#include "../graph.h"

const void graph::assign_function(
	int (*function)()
) {
	this->assigned_function = function;
}

const int graph::get_maximal_buffer() {
	return this->maximal_value;
}

const int graph::get_minimal_buffer() {
	int minimal = INT32_MAX;
	for (
		int val : this->buffer
		) minimal = std::min(val, minimal);
	return minimal;
}

const int graph::get_average_buffer() {
	long long sum = 0;

	if (
		buffer.size() == 0
		) return 0;

	for (
		int val : this->buffer
		) sum += val; 
	return (
		sum / this->buffer.size()
		);
}