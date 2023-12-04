#include "Graph.h"

void Graph::MenageValuesSize()
{
	wxCoord HorizontalLenght = this->GetClientSize().x - 20;
	int Difference = HorizontalLenght - this->Values.size(); 

	if (
		0 < Difference
		) return; 

	std::vector<int> RehashedBuffer; 

	for (int Iterator = std::abs(Difference); Iterator < this->Values.size(); Iterator++) {
		RehashedBuffer.push_back(this->Values[Iterator]);
	}

	this->Values = RehashedBuffer;
}

void Graph::HandleWindowTitle() {
	if (
		this->Values.size() == 0
		) return; 

	int Procentage = static_cast<int>(float(float(this->Values[this->Values.size() - 1]) / float(this->MaximalValueSeen) * 100.0)); 
	this->SetTitle(this->Name + " | " + std::to_string(Procentage) + "%");
}

void Graph::UpdateBuffer()
{
	std::thread RealtimeUpdate([&] {
		do {
			std::this_thread::sleep_for(std::chrono::milliseconds(400));

			this->Values.push_back(
				this->StatusFunction()
			); this->MenageValuesSize();
			
			this->HandleWindowTitle();

			this->Update(); this->Refresh();
			//wxLogMessage(std::to_string(this->Values.size()).c_str());
		} while (
			true
			);
		});

	RealtimeUpdate.detach();
}