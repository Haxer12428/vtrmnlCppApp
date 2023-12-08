#include "../Cmd.h"

const void Cmd::SETUP_REGISTER_VARIABLES(
	const std::filesystem::path& _Path
) {
	this->_AT = _Path; 
}