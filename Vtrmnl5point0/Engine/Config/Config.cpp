#include "../Engine.h"

Engine::Config::Config(
	const std::filesystem::path& _PATH
) : _PATH(_PATH) {
	this->HandleFile();
}

void Engine::Config::HandleFile() {
	std::filesystem::path _CUT = this->_PATH; _CUT.remove_filename();
	std::filesystem::create_directories(_CUT);

	if (
		std::filesystem::is_regular_file(this->_PATH)
		) return; 

	std::fstream _FILE; _FILE.open(
		this->_PATH, std::ios::out
	);
	_FILE << ""; _FILE.close();
}

const std::string Engine::Config::Desire(
	const std::string& _NAME, const std::string& _DEFAULTvalue
) {
	std::string BufferRead; std::string _BUF; std::string Buffer; 

	std::fstream _FILE; _FILE.open(
		this->_PATH, std::ios::in
	);

	if (
		!_FILE.is_open()
		) return "NULL";

	while (
		std::getline(_FILE, _BUF)
		) { 
		Buffer += _BUF + "\n";

		std::string _CUT = _BUF; 

		size_t _pSTART = Engine::String::Find(_BUF, "\"");

		if (
			_pSTART == -1
			) throw Engine::Debug::Object("Config file syntax is corrupted", Engine::Debug::FAIL);
		_pSTART++; 

		_CUT = _CUT.substr(_pSTART); 
		const size_t _pEND = Engine::String::Find(_CUT, "\"");

		if (
			_pEND == -1
			) throw Engine::Debug::Object("Config file syntax is corrupted", Engine::Debug::FAIL);

		_CUT.resize(_pEND);
		const std::string _PARAM = _CUT;

		if (
			_PARAM == _NAME
			) {
			size_t _HALF = Engine::String::Find(_BUF, ":");
			std::string _hCUT = _BUF.substr(_HALF);

			size_t _vSTART = Engine::String::Find(_hCUT, "\"");

			if (
				_vSTART == -1
				) throw Engine::Debug::Object("Config file syntax is corrupted", Engine::Debug::FAIL);
			_vSTART++;

			_hCUT = _hCUT.substr(_vSTART);
			const size_t _vEND = Engine::String::Find(_hCUT, "\"");

			if (
				_vEND == -1
				) throw Engine::Debug::Object("Config file syntax is corrupted", Engine::Debug::FAIL);

			_hCUT.resize(_vEND);

			const std::string _VALUE = _hCUT;

			return _VALUE;
		}
	}

	_FILE.close();

	_FILE.open(
		this->_PATH, std::ios::out
	); 

	_FILE << Buffer + "\"" + _NAME + "\" : \"" + _DEFAULTvalue + "\"";

	_FILE.close();

	return "NULL";
}