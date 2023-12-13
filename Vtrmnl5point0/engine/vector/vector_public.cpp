#include "../engine.h"

const std::string engine::vector::transform_string_vector_to_string(
	const std::vector<std::string> &buffer
) {
	std::string transformed = "";

	for (
		std::string current_buffer_line : buffer
		) {
		transformed += current_buffer_line + "\n";
	}

	return transformed;
}

const std::vector<int> engine::vector::transform_string_vector_to_int_vector(
	const std::vector<std::string>& buffer
) {
	std::vector<int> buffer_transformed; 
	for (
		std::string line : buffer
		) {
		buffer_transformed.push_back(std::stoi(line));
	}
	return buffer_transformed;
}

const std::vector<std::string> engine::vector::find_in_phrases(
	const std::string& str, const std::string& phrases
) {
	std::vector<std::string> buffer;
	std::string str_cut = str;

	const size_t phrases_lenght = phrases.length();

	do {
		const size_t found_first_phrase = engine::string(str_cut).find_phrase(phrases);

		if (
			found_first_phrase == std::string::npos
			) break; 

		const size_t found_second_phrase = engine::string(str_cut.substr(found_first_phrase + 1)).find_phrase(phrases);

		if (
			found_second_phrase == std::string::npos
			) break; 

		const std::string found_in_phrases = str_cut.substr(found_first_phrase + 1, found_second_phrase);

		buffer.push_back(
			found_in_phrases
		);

		str_cut = str_cut.substr(found_in_phrases.length() + phrases_lenght * 2);
	} while (
		true
		);
	return buffer;
}