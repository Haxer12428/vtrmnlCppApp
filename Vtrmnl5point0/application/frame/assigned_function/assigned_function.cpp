#include "../frame.h"

const void frame::assigned_function_push(
	const frame::assigned_function& function
) {
	this->assigned_functions.push_back(
		function
	);
}

const bool frame::assigned_function_find_and_call(
	const std::string& name, const std::vector<std::string>& arguments
) {
	for (
		frame::assigned_function function : this->assigned_functions
		) {
		const std::string function_name = function.get_name();
		if (
			function_name == name
			) return function.call(
				this, arguments
			); 
	}
	return false; 
}