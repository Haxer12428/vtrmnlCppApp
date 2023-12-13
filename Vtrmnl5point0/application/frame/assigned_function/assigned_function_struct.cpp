#include "../frame.h"

frame::assigned_function::assigned_function(
	void* (frame::* function)(
		const std::vector<std::string>&
		), 
	const std::string& name
) : function(function), name(name)
{

}

const std::string frame::assigned_function::get_name() const {
	return this->name; 
}

const bool frame::assigned_function::call(
	frame* obj, const std::vector<std::string> &arguments 
) const {
	try {
		(obj->*(this->function))(arguments);
	}
	catch (
		const std::exception /*ex*/
		) {
		return false; 
	}
	return true; 
}