#include "../Cmd.h"

int _MEMSTATUSSELF()
{
	Engine::Process Process = Engine::Process();
	Process.FindPID(GetCurrentProcessId());

	return Engine::Memory::ofProcess(Process).Usage(Engine::Memory::KB);
}

void Cmd::SETUP_COMMANDS() {


	// [ MEMORY USAGE ] 
	this->COMMAND_MEMORY_USAGE_GRAPH = new Render::Graph("Terminal Memory Usage", 600, 450, -1, "KB"); 
	this->COMMAND_MEMORY_USAGE_GRAPH->SetRefreshRate(std::chrono::milliseconds(400));
	this->COMMAND_MEMORY_USAGE_GRAPH->AssingStatusFunction(_MEMSTATUSSELF);
	this->COMMAND_MEMORY_USAGE_GRAPH->SetParent(this);

	Cmd::COMMAND_STRUCT COMMAND_MEMORY_USAGE_STRUCT(" Memory Usage ", &Cmd::COMMAND_MEMORY_USAGE);
	
	this->PUBLIC_COMMAND_PUSH(COMMAND_MEMORY_USAGE_STRUCT);

	// [ SETTINGS ] 
	Cmd::COMMAND_STRUCT COMMAND_SETTINGS_STRUCT(" Settings ", &Cmd::COMMAND_SETTINGS);

	this->PUBLIC_COMMAND_PUSH(COMMAND_SETTINGS_STRUCT);

	// [ (~) ] 
	Cmd::COMMAND_STRUCT COMMAND_REFRESH_STRUCT("(~) ", &Cmd::COMMAND_REFRESH); 
	
	this->PUBLIC_COMMAND_PUSH(COMMAND_REFRESH_STRUCT);
}