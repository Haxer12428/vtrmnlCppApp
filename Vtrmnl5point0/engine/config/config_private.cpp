#include "../engine.h"

const bool engine::config::file_available() const {
	return std::filesystem::is_regular_file(this->get_path());
}

const bool engine::config::make_desire(
	const std::string &name, const std::string& value 
) const {
	const std::filesystem::path config_path = this->get_path();
	std::vector<std::string> config_file_buffer_vector = engine::file(config_path).get_buffer_in_vector();

	config_file_buffer_vector.push_back("\"" + name + "\" : \"" + value + "\"");

	engine::file(config_path).write_vector_buffer(config_file_buffer_vector);

	return true; 
}

const bool engine::config::make_file() const {
	const std::filesystem::path config_path = this->get_path();
	std::filesystem::path config_path_dir = config_path; config_path_dir.remove_filename();

	std::filesystem::create_directories(config_path_dir);

	std::fstream config_file; config_file.open(
		config_path, std::ios::out
	);

	config_file << ""; 
	config_file.close(); 

	return this->file_available();
}