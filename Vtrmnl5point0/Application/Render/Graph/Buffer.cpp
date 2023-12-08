#include "../Render.h"

void Render::Graph::UpdateTitle(
	const int& _PROCENTAGE
) {
	this->SetTitle(
		(this->_NAME + " | " + std::to_string(_PROCENTAGE) + "%")
	);
}

void Render::Graph::UpdateMaximal(
	const int& _VALUE
) {
	if (
		this->_LOCKED
		) return;
	this->_MAXIMAL = std::max(this->_MAXIMAL, _VALUE);
}

void Render::Graph::LimitBuffer() {
	int _SIZE = (this->GetClientSize().x) / (this->_STATUSLENGHT + this->_STATUSSPACING);
	size_t _BUFFERSIZE = this->Buffer.size();

	if (
		_BUFFERSIZE <= _SIZE
		) return;

	std::vector<int> _NEW; 
	int _DIF = (_BUFFERSIZE - _SIZE) - 1;

	for (
		size_t Iterator = _DIF; Iterator < _BUFFERSIZE; Iterator++
		) {
		_NEW.push_back(this->Buffer[Iterator]);
	}

	this->Buffer = _NEW;
}

void Render::Graph::RefreshBuffer() {
	std::thread _REF(
		[&] {
			do {
				std::this_thread::sleep_for(
					std::chrono::milliseconds(this->_REFRESH)
				);

				const int _STATUSresponse = this->_STATUS();

				this->Buffer.push_back(
					_STATUSresponse
				);

				this->_BUFFERUNLIMITED = this->Buffer;

				this->LimitBuffer(); this->UpdateMaximal(this->Buffer[this->Buffer.size() - 1]); 

				this->UpdateTitle(
					int((float(this->Buffer[this->Buffer.size() - 1]) / float(this->_MAXIMAL)) * 100)
				);

				this->Refresh();
			} while (
				true
				);
		});
	_REF.detach();
}