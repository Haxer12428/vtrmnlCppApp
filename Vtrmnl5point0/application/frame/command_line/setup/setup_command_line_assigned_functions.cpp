#include "../../frame.h"

// [ GET_FILES ] 
	void* frame::assgined_function_command_line_get_files(
		const std::vector<std::string>& arguments
	) {
		//determinate recursivity 
		bool is_recursive = engine::vector().find_value<std::string>(arguments, "recursive") != -1;
		
		//determinate path 
		const size_t path_at_i = engine::vector().find_phrase(arguments, "path=");

		if ( // no path? 
			path_at_i == std::string::npos
			) {
			throw std::exception(
				"path not given?"
			);
		}

		const std::vector<std::string> path_found_in_phrases = engine::vector::find_in_phrases(
			arguments[path_at_i], "\""
		);

		if ( // no path? 
			path_found_in_phrases.size() == 0 
			) {
			throw std::exception(
				"path not given?"
			);
		}

		const std::filesystem::path path = path_found_in_phrases[0];

		if (
			is_recursive
			) {
			this->assigned_function_command_line_get_files_recursive(path); return 0;
		}
		this->assigned_function_command_line_get_files_non_recursive(path); return 0; 
	}
	// [ RECURSIVE ] 
		const void frame::assigned_function_command_line_get_files_recursive(
			const std::filesystem::path& path
		) {
			this->handle_command_line_buffer_push_line(path.string() + ":");
			for (
				const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(path)
				) {
				if (
					entry.is_regular_file()
					) {
					this->handle_command_line_buffer_push_line(
						" " + entry.path().string()
					);
				}
			}
		}
	// [ NON_RECURSIVE ] 
		const void frame::assigned_function_command_line_get_files_non_recursive(
			const std::filesystem::path& path
		) {
			this->handle_command_line_buffer_push_line(path.string() + ":");
			for (
				const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)
				) {
				if (
					entry.is_regular_file()
					) {
					this->handle_command_line_buffer_push_line(
						" " + entry.path().string()
					);
				}
			}
		}

// [ SYSTEM32_SHUTDOWN ] 
void* frame::assigned_function_command_line_system32_shutdown(
	const std::vector<std::string>& arguments
	) {
	system("shutdown /s /t 0"); return 0;
}


// [ SYSTEM32_PROCESS_MEMORY_USAGE ] 
graph* assigned_function_comand_line_system32_process_memory_usage_graph_obj;

int assigned_function_comand_line_system32_process_memory_usage_graph_pid = (
	-1
	);

std::string assigned_function_comand_line_system32_process_memory_usage_graph_name = (
	""
	);

int assigned_function_comand_line_system32_process_memory_usage_graph_function() {
	if (
		assigned_function_comand_line_system32_process_memory_usage_graph_pid == -1 && assigned_function_comand_line_system32_process_memory_usage_graph_name.length() == 0
		) return -1; 

	engine::process process;
	
	if (
		assigned_function_comand_line_system32_process_memory_usage_graph_pid == -1
		) {
		process.find_by_name(assigned_function_comand_line_system32_process_memory_usage_graph_name);
	}
	else {
		process.find_by_pid(assigned_function_comand_line_system32_process_memory_usage_graph_pid);
	}

	return engine::memory(
		process
		).get_usage(engine::memory::MB);
}

void* frame::assigned_function_comand_line_system32_process_memory_usage(
	const std::vector<std::string>& arguments
) {
	const bool pid_found = engine::vector().find_phrase(arguments, "pid=") != -1;
	const bool name_found = engine::vector().find_phrase(arguments, "name=") != -1; 

	if ( // double arguments?
		pid_found && name_found
		) throw std::exception(
			"double arguments?"
		);

	if ( // what process?
		!pid_found && !name_found
		) throw std::exception(
			"what process?"
		);

	if ( // by pid 
		pid_found
		) {
		const std::vector<std::string> pid_ref = engine::vector::find_in_phrases(arguments[engine::vector().find_phrase(arguments, "pid=")], "\"");
	
		if ( // pid: no value given? 
			pid_ref.size() == 0
			) throw std::exception(
				"pid: no value given?"
			);

		try { // assign values 
			assigned_function_comand_line_system32_process_memory_usage_graph_pid = std::stoi(pid_ref[0]);
			assigned_function_comand_line_system32_process_memory_usage_graph_name = "";
		}
		catch ( // pid: incorrect format? 
			const std::exception /*ex*/
			) {
			throw std::exception(
				"pid: incorrect format?"
			);
		}
	}
	else { // by name 
		const std::vector<std::string> name_ref = engine::vector::find_in_phrases(arguments[engine::vector().find_phrase(arguments, "name=")], "\"");

		if ( // name: no value given?
			name_ref.size() == 0
			) throw std::exception(
				"name: no value given?"
			); 

		assigned_function_comand_line_system32_process_memory_usage_graph_pid = -1;
		assigned_function_comand_line_system32_process_memory_usage_graph_name = name_ref[0];
	}

	const bool in_graph = engine::vector().find_value<std::string>(arguments, "graph") != -1; 

	if ( // graph representation 
		in_graph
		) {
		const bool graph_skip_buffer = engine::vector().find_value<std::string>(arguments, "graph.skip.buffer") != -1;

		if (
			graph_skip_buffer
			) {
			assigned_function_comand_line_system32_process_memory_usage_graph_obj->clear_buffer();
		}

		const bool graph_skip_max = engine::vector().find_value<std::string>(arguments, "graph.skip.max") != -1;

		if (
			graph_skip_max
			) {
			assigned_function_comand_line_system32_process_memory_usage_graph_obj->clear_max();
		}

		const bool graph_large = engine::vector().find_value<std::string>(arguments, "graph.large") != -1;
		const bool graph_medium = engine::vector().find_value<std::string>(arguments, "graph.medium") != -1;

		if (
			graph_large
			) {
			assigned_function_comand_line_system32_process_memory_usage_graph_obj->SetSize(1200, 900);
		}
		else if (
			graph_medium
			) {
			assigned_function_comand_line_system32_process_memory_usage_graph_obj->SetSize(700, 550);
		}

		assigned_function_comand_line_system32_process_memory_usage_graph_obj->Show(); 
		return 0; 
	}

	// command line string representation 
	this->handle_command_line_buffer_push_line(
		std::to_string(assigned_function_comand_line_system32_process_memory_usage_graph_function()) + " MB"
	);

	return 0; 
}

// [ CLEAR_BUFFER ] 
void *frame::assigned_function_command_line_terminal_clear_buffer(
	const std::vector<std::string>& arguments
) {
	const bool clear_all = engine::vector().find_value<std::string>(arguments, "clear.all") != -1;
	const bool clear_lines = engine::vector().find_phrase(arguments, "clear.lines=") != -1;

	if ( // what to clear?
		!clear_all && !clear_lines
		) throw std::exception(
			"what to clear?"
		);

	if ( // clear_all 
		clear_all
		) {
		this->draw_command_line_buffer_original = {};
		this->draw_command_line_buffer_formated = {}; 

		this->Refresh();
		return 0;
	}

	// clear_lines
	try {
		const int clear_amount = std::stoi(engine::vector::find_in_phrases(arguments[
			engine::vector().find_phrase(arguments, "clear.lines=")
		], "\"")[0]);

		std::vector<std::string> cleared_buffer = {}; 

		for (
			int iterator = clear_amount; iterator < this->draw_command_line_buffer_original.size(); iterator++
			) {
			cleared_buffer.push_back(
				this->draw_command_line_buffer_original[iterator]
			); 
		}

		this->draw_command_line_buffer_original = cleared_buffer;

		this->handle_command_line_buffer_format(this->draw_command_line_buffer_original, this->draw_command_line_text_help_get_area_size().x);

		this->Refresh();
	}
	catch (
		const std::exception& ex
		) {
		throw ex; 
	}
	return 0;
} 

const void frame::setup_command_line_assigned_functions() {
	this->assigned_function_push(
		frame::assigned_function(&frame::assgined_function_command_line_get_files, "get.files")
	);

	this->assigned_function_push(
		frame::assigned_function(&frame::assigned_function_command_line_system32_shutdown, "system32.shutdown")
	);

	this->assigned_function_push(
		frame::assigned_function(&frame::assigned_function_comand_line_system32_process_memory_usage, "system32.process.memory.usage")
	);

	assigned_function_comand_line_system32_process_memory_usage_graph_obj = new graph(this, "system32.monitor.memory.usage", 0, "MB");

	assigned_function_comand_line_system32_process_memory_usage_graph_obj->Show(false);

	assigned_function_comand_line_system32_process_memory_usage_graph_obj->assign_function(
		assigned_function_comand_line_system32_process_memory_usage_graph_function
	);

	this->assigned_function_push(
		frame::assigned_function(&frame::assigned_function_command_line_terminal_clear_buffer, "terminal.buffer.clear")
	);
}