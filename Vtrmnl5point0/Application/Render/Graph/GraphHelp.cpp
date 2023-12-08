#include "../Render.h"

const int Render::Graph::GetMaximalNotedValue() {
	int _MAX = 0; 

	for (
		int _VAL : this->_BUFFERUNLIMITED
		) {
		_MAX = std::max(_MAX, _VAL);
	}
	
	return _MAX;
}

const int Render::Graph::GetMinimalNotedValue() {
	int _MIN = 0; 

	for (
		int _VAL : this->_BUFFERUNLIMITED
		) {
		_MIN = std::min(_MIN, _VAL); 
	}

	return _MIN;
}

const int Render::Graph::GetAverageNotedValue() {
	int _AVERAGE = 0; int _SUM = 0; 

	for (
		int _VAL : this->_BUFFERUNLIMITED
		) {
		_SUM += _VAL;
	}

	if (
		this->_BUFFERUNLIMITED.size() <= 1
		) return _AVERAGE; 

	_AVERAGE = int(_SUM / int(this->_BUFFERUNLIMITED.size() - 1));

	return _AVERAGE; 
}