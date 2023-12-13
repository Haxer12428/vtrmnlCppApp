#include "../engine.h"

engine::config::config(
	const std::filesystem::path& file_path
) : file_path(file_path)
{
	if (
		!this->file_available()
		) {
		this->make_file(); throw std::exception("Corrupted/unavailable config file.");
	}
}