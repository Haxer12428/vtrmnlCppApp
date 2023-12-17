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

const void frame::setup_command_line_assigned_functions() {
	this->assigned_function_push(
		frame::assigned_function(&frame::assgined_function_command_line_get_files, "get.files")
	);

	this->assigned_function_push(
		frame::assigned_function(&frame::assigned_function_command_line_system32_shutdown, "system32.shutdown")
	);
}