#include "../../frame.h"

// [ ASSIGNED_FUNCTION_MOUSE_INTERACTIVE_PANEL_MEMORY_USAGE ] 
int assigned_function_mouse_interactive_panel_memory_usage_handle() {
	engine::process process = engine::process();

	const bool process_found = process.find_by_pid(
		GetCurrentProcessId()
	);

	if (
		process_found == false
		) {
		wxLogMessage("(?) Unable to resolve process id."); return -1;
	}

	const int process_memory_usage = engine::memory(process).get_usage(engine::memory::KB);

	return process_memory_usage; 
}

void *frame::assigned_function_mouse_interactive_panel_memory_usage(
	const std::vector<std::string> &
) {
	this->assigned_function_mouse_interactive_panel_memory_usage_graph->Show(
		not this->assigned_function_mouse_interactive_panel_memory_usage_graph->IsShown()
	); return 0;
}


const void frame::setup_mouse_interactive_panel_assigned_functions() {
	// [ ASSIGNED_FUNCTION_MOUSE_INTERACTIVE_PANEL_MEMORY_USAGE ]
	this->assigned_function_mouse_interactive_panel_memory_usage_graph = new graph(this, "Terminal Memory Usage Graph", 0, "KB");

	this->assigned_function_mouse_interactive_panel_memory_usage_graph->Show(false);

	this->assigned_function_mouse_interactive_panel_memory_usage_graph->assign_function(
		assigned_function_mouse_interactive_panel_memory_usage_handle
	);

	this->assigned_function_push(frame::assigned_function(&frame::assigned_function_mouse_interactive_panel_memory_usage, "Memory Usage"));
}