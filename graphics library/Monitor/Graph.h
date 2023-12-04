#pragma once
#include <wx/wx.h>
#include <vector>
#include <thread>

class Graph : public wxFrame
{
public:
	Graph(const wxString& Name, const int MAXIMAL_SIZE);

	//_CONFIGURATIOM
	void AssignStatusFunction(
		int (*function)()
	); 

private:
	//_GRAPH 
	void ConfigureBinds();

	//_HANDLE
	void UpdateBuffer();

	void MenageValuesSize();

	void HandleWindowTitle(); 

	//_RENDER
	void RenderGraph(
		wxPaintEvent &evt 
	); 

public:
	int MaximalValueSeen = 0;
	int MaximalValueSeenLocked = false;

	const wxString Name; 
	std::vector<int> Values;
	int (*StatusFunction)();
};


