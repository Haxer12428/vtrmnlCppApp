#include "../engine.h"

std::filesystem::path engine::config::get_path() const {
	return this->file_path;
}

const std::string engine::config::desire(
	const std::string& name, const std::string& default_value
) const {
	std::fstream config_file; std::string config_line; 
	
	config_file.open(
		this->get_path(), std::ios::in
	);

	while (
		std::getline(config_file, config_line)
		) {

		try {
			const std::vector<std::string> phrases_found = engine::vector::find_in_phrases(
				config_line, "\""
			);

			const std::string phrase_name = phrases_found[0];
			const std::string phrase_value = phrases_found[1];

			if (
				phrase_name == name
				) {
				config_file.close();

				return phrase_value;
			}
		}
		catch (
			const std::exception& /*ex*/
			) {
			config_file.close();
			this->make_file(); return default_value;
		}
	}
	config_file.close();

	this->make_desire(name, default_value);

	return default_value;
}