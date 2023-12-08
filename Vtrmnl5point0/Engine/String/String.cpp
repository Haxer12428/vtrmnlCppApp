#include "../Engine.h"

const size_t Engine::String::Find(
	const std::string& _STR, const std::string &_FIND
) {
	for (
		size_t Iterator = 0; Iterator < _STR.length(); Iterator++
		) {
		std::string _CSTR = "";

		for (
			size_t iTransform = 0; iTransform < _FIND.length(); iTransform++
			) {
			size_t _SUM = Iterator + iTransform;

			if (
				_STR.size() <= _SUM
				) return -1; 

			_CSTR += std::string(1, _STR.at(_SUM));
		}

		if (
			_CSTR == _FIND
			) {
			return Iterator;
		}
	}
	return -1; 
}

const std::vector<std::string> Engine::String::GetVector(
	const std::string& _STR
) {
	std::vector<std::string> _VEC; 
	std::string _CUT = _STR; std::string _CUT2 = _STR;

	do {
		const size_t _FOUND = Engine::String::Find(_CUT, ",");

		if (
			_FOUND == -1
			) {
			_VEC.push_back(_CUT); break;
		}

		_CUT2.resize(_FOUND); _VEC.push_back(_CUT2); _CUT = _CUT.substr(_FOUND + 1); _CUT2 = _CUT;
	} while (
		true
		); 

	return _VEC; 
}