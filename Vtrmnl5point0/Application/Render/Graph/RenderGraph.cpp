#include "../Render.h"

void Render::Graph::RenderLine(
	wxPaintDC &dc
) {
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(*wxWHITE_PEN);

	dc.DrawLine(
		wxPoint(0, this->GetClientSize().y - this->_INFORESERVED), wxPoint(this->GetClientSize().x, this->GetClientSize().y - this->_INFORESERVED)
	);
}

void Render::Graph::RenderStatus(
	wxPaintDC &dc
) {
	int _STATUSRESERVED = this->GetClientSize().y - this->_INFORESERVED - 1; 

	for (
		size_t Iterator = 0; Iterator < this->Buffer.size(); Iterator++
		) {
		int _VALUE = this->Buffer[Iterator];

		float _PROCENTAGE = float(_VALUE) / float(this->_MAXIMAL);

		int _HEIGHT = static_cast<int>(_STATUSRESERVED * _PROCENTAGE);
		int _LENGHT = this->_STATUSLENGHT;

		int _POSITIONX = Iterator * (_LENGHT + this->_STATUSSPACING); 
		int _POSITIONY = _STATUSRESERVED - _HEIGHT;

		wxBrush _BRUSHc = wxColor(0, 180, 255);
		wxPen _PENc = wxColor(0, 180, 255);

		if (
			_PROCENTAGE > 0.4
			) {
			_BRUSHc = *wxGREEN_BRUSH; _PENc = *wxGREEN_PEN;
		}

		if (
			_PROCENTAGE > 0.7
			) {
			_BRUSHc = *wxRED_BRUSH; _PENc = *wxRED_PEN;
		}

		dc.SetBrush(_BRUSHc); dc.SetPen(_PENc);

		dc.DrawRectangle(
			_POSITIONX, _POSITIONY, _LENGHT, _HEIGHT
		);
	}
}

void Render::Graph::RenderInfo(
	wxPaintDC &dc
) {
	int _AVERAGE, _MIN, _MAX, _CURRENT; 

	_AVERAGE = this->GetAverageNotedValue();
	_MIN = this->GetMinimalNotedValue();
	_MAX = this->GetMaximalNotedValue();
	
	if (
		this->Buffer.size() == 0
		) return;

	_CURRENT = this->Buffer[this->Buffer.size() - 1];

	//_FONT 
	wxFont _FONT(
		10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_HEAVY
	);

	_FONT.SetFaceName("Hack");
	
	dc.SetFont(_FONT);

	//_RENDER
	const std::string _TEXT = "Current " + std::to_string(_CURRENT)  + this->_UNIT + " - Min " + std::to_string(_MIN) + this->_UNIT + " - Avg " + std::to_string(_AVERAGE) + this->_UNIT + " - Max " + std::to_string(_MAX) + this->_UNIT;
	
	dc.SetTextForeground(wxColor(255, 255, 255));
	wxSize _TEXTSIZE = dc.GetTextExtent(_TEXT);

	int _X, _Y; 

	_X = ((this->GetClientSize().x / 2) - _TEXTSIZE.x / 2);
	_Y = this->GetClientSize().y - this->_INFORESERVED/2 - ((this->_INFORESERVED / 2) - _TEXTSIZE.y / 2);

	dc.DrawText(_TEXT, _X, _Y);
}

void Render::Graph::RenderGraph(
	wxPaintEvent& evt
) {
	wxPaintDC dc(this);

	this->RenderLine(dc); 
	this->RenderStatus(dc); 
	this->RenderInfo(dc);
}