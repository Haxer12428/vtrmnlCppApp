#include "../engine.h"

const std::filesystem::path engine::file::get_path() const {
	return this->file_path;
}

const void engine::file::set_path(
	const std::filesystem::path& path
) {
	this->file_path = path; 
}

const bool engine::file::write_vector_buffer(
	const std::vector<std::string>& buffer
) const {
	try {
		std::fstream file; file.open(
			this->get_path(), std::ios::out
		);

		file << engine::vector::transform_string_vector_to_string(buffer); file.close();
	} 
	catch (
		const std::exception /*ex*/
		) {
		return false; 
	}

	return true; 
}

const std::vector<std::string> engine::file::get_buffer_in_vector() {
	std::vector<std::string> buffer; std::string buffer_line; 
	
	std::fstream file; file.open(
		this->get_path(), std::ios::in
	);

	while (
		std::getline(file, buffer_line)
		) {
		buffer.push_back(buffer_line);
	}
	file.close();

	return buffer; 
}