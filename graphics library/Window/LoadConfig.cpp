#include "Window.h"

Window::LoadConfig::LoadConfig(
	Window* WindowPtr
) : WindowPtr(WindowPtr) {

	std::filesystem::path ConfigPath = "C:/vtrmnl3/data/config.txt";

	this->PrepareConfig(ConfigPath);

	this->LoadWxFrameSize();
	this->LoadWxFrameBackground();
}

void Window::LoadConfig::LoadWxFrameSize()
{
	int Height, Lenght; 

	Height = ConfigSystem->GetVariable<int>("$WindowSizeY");

	Lenght = ConfigSystem->GetVariable<int>("$WindowSizeX");

	this->WindowPtr->SetSize(
		wxSize(Lenght, Height)
	);
}

void Window::LoadConfig::LoadWxFrameBackground()
{
	this->WindowPtr->SetBackgroundColour(
		wxColor(38, 38, 38)
	);
}

void Window::LoadConfig::PrepareConfig(
	std::filesystem::path& ConfigPath
) {
	this->ConfigSystem = new Config(ConfigPath);

	if (
		!std::filesystem::exists(ConfigPath.remove_filename())
		) std::filesystem::create_directories(ConfigPath.remove_filename());

	ConfigSystem->NewConfigVariable("$WindowSizeX", std::to_string(800));
	ConfigSystem->NewConfigVariable("$WindowSizeY", std::to_string(800));

	ConfigSystem->HandleConfigFile();
}