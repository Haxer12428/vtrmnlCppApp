#include "../engine.h"

const std::string engine::string::get_string() const {
	return this->str;
}

const void engine::string::set_string(
	const std::string& str
) {
	this->str = str; 
}

const std::vector<std::string> engine::string::get_vector() const {
	const std::string str = this->get_string();

	std::vector<std::string> buffer;
	std::string cut = str; std::string cut2 = str;

	do {
		const size_t found_at = engine::string(cut).find_phrase(",");

		if (
			found_at == std::string::npos
			) {
			buffer.push_back(
				cut
			); break;
		}

		cut2.resize(
			found_at
		);
		
		buffer.push_back(
			cut2
		); 
		
		cut = cut.substr(
			found_at + 1
		); 
		
		cut2 = cut;
	} while (
		true
		);

	return buffer; 
}

const size_t engine::string::find_phrase(
	const std::string& phrase
) const {
	const std::string str = this->get_string();

	const size_t phrase_lenght = phrase.length(); 
	const size_t string_lenght = str.length(); 

	if (
		string_lenght < phrase_lenght || phrase_lenght == 0 || string_lenght == 0
		) return -1; 

	const size_t maximal_lenght = string_lenght - phrase_lenght;
	size_t at = 0; 

	do {
		if (
			at > maximal_lenght
			) return -1; 

		std::string current_found_phrase = str.substr(at);
		current_found_phrase.resize(phrase_lenght);

		if (
			current_found_phrase == phrase
			) return at;
		at++; 
	} while (
		true
		);
	return -1; 
}