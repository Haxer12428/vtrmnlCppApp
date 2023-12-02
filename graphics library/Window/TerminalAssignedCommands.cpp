#include "Window.h"

const std::vector<Window::CommandFunc>& Window::GetTerminalAssignedCommands()
{
	return this->TerminalAssignedCommands;
}

