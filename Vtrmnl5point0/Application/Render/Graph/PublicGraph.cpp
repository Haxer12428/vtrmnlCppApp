#include "../Render.h"

void Render::Graph::AssingStatusFunction(
	int (*_STATUSf)()
) {
	this->_STATUS = _STATUSf;
}

const bool Render::Graph::IsLocked() {
	return this->_LOCKED;
}

void Render::Graph::LockMaximal(
	const bool& _LOCK
) {
	this->_LOCKED = _LOCK;
}

void Render::Graph::SetMaximal(
	const int& _MAX
) {
	this->_MAXIMAL = _MAX;
}

void Render::Graph::SetRefreshRate(
	const std::chrono::milliseconds &_REF
) {
	this->_REFRESH = _REF;
}
