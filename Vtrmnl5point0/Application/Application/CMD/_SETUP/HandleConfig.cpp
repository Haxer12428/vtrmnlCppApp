#include "../Cmd.h"

const void Cmd::SETUP_CONFIG_HANDLE(
	const std::filesystem::path& _AT 
) {
	this->Config = new Engine::Config(
		_AT.string() + "\\config.cfg"
	);

	std::vector<int> BACKGROUND_STYLE_COLOR = Engine::Vector::TransformStringToInt(Engine::String::GetVector(this->Config->Desire("$BACKGROUND_STYLE_COLOR", "35,39,41")));

	std::vector<int> DEFAULT_SIZE = Engine::Vector::TransformStringToInt(Engine::String::GetVector(this->Config->Desire("$DEFAULT_SIZE", "1000,750")));

	std::vector<std::string> MOUSE_INTERFACE_FONT_INFO = Engine::String::GetVector(this->Config->Desire("$MOUSE_INTERFACE_FONT", "Hack,11"));

	const int MOUSE_INTERFACE_ADDITIONAL_RESERVED_SPACE = std::stoi(this->Config->Desire("$MOUSE_INTERFACE_ADDITIONAL_RESERVED_SPACE", "12"));

	std::vector<int> MOUSE_INTERFACE_COLOR_BACKGROUND = Engine::Vector::TransformStringToInt(Engine::String::GetVector(this->Config->Desire("$MOUSE_INTERFACE_COLOR_BACKGROUND", "53,60,62")));
	std::vector<int> MOUSE_INTERFACE_COLOR_TEXT = Engine::Vector::TransformStringToInt(Engine::String::GetVector(this->Config->Desire("$MOUSE_INTERFACE_COLOR_TEXT", "255,255,255,255")));
	
	this->SETUP_BACKGROUND_STYLE(BACKGROUND_STYLE_COLOR[0], BACKGROUND_STYLE_COLOR[1], BACKGROUND_STYLE_COLOR[2]);
	this->SETUP_SIZE(DEFAULT_SIZE[0], DEFAULT_SIZE[1]);
	this->SETUP_MOUSE_INTERFACE_FONT(MOUSE_INTERFACE_FONT_INFO[0], std::stoi(MOUSE_INTERFACE_FONT_INFO[1]));
	this->SETUP_MOUSE_INTERFACE_ADDITIONAL_RESERVED_SPACE(MOUSE_INTERFACE_ADDITIONAL_RESERVED_SPACE);
	this->SETUP_MOUSE_INTERFACE_COLORS(
		MOUSE_INTERFACE_COLOR_TEXT[0], MOUSE_INTERFACE_COLOR_TEXT[1], MOUSE_INTERFACE_COLOR_TEXT[2], MOUSE_INTERFACE_COLOR_BACKGROUND[0], MOUSE_INTERFACE_COLOR_BACKGROUND[1], MOUSE_INTERFACE_COLOR_BACKGROUND[2]
	);
}