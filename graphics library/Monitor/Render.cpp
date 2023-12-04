#include "Graph.h"

void Graph::RenderGraph(
	wxPaintEvent& evt
) {
	wxPaintDC dc(this);

	for (
		size_t Iterator = 0; Iterator < this->Values.size(); Iterator++
		) {

		int Value = this->Values[Iterator];

		if (Value > this->MaximalValueSeen && this->MaximalValueSeenLocked == false)
			MaximalValueSeen = Value;

		dc.SetPen(*wxYELLOW_PEN);
		dc.SetBrush(*wxYELLOW_BRUSH);
		int x = int(Iterator); int Height = int(float(this->GetClientSize().y) * (float(Value) / float(MaximalValueSeen)));

		dc.DrawRectangle(x, this->GetClientSize().y, 1, -Height);
	}
}