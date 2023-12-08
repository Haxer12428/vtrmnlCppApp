#include "../Cmd.h"

const void Cmd::SETUP_REGISTER_VARIABLES(
	const std::filesystem::path& _Path
) {
	this->Config = new Engine::Config(
		_AT.string() + "\\config.cfg"
	);

	this->_AT = _Path; 
}