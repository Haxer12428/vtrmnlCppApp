#pragma once
#include <wx/wx.h>
#include <string>
#include <thread>

namespace Render
{
	class Graph : public wxFrame
	{
	public:
		Graph(
			const std::string& _NAME, const int& _SIZEX, const int& _SIZEY, const int& _MAXIMAL, const std::string& _UNIT
		);

		void AssingStatusFunction(
			int (*function)()
		); 

		void LockMaximal(
			const bool& _LOCK
		);

		const bool IsLocked();

		void SetMaximal(
			const int& _MAX
		);

		void SetRefreshRate(
			const std::chrono::milliseconds &_REF
		);

	private:
		void DestroyOnClose(
			wxCloseEvent& evt
		); 

		void LimitBuffer();

		void RefreshBuffer();

		void ConfigureBinds();

		void ConfigureMaximal(
			const int &_MAX
		); 

		void RenderGraph(
			wxPaintEvent& evt 
		); 

		void RenderLine(
			wxPaintDC &dc
		); 

		void RenderInfo(
			wxPaintDC &dc
		);

		void RenderStatus(
			wxPaintDC &dc
		);

		void UpdateTitle(
			const int &_PROCENTAGE
		);

		void UpdateMaximal(
			const int &_MAXIMAL
		);

		//_HELP 
		const int GetMaximalNotedValue();
		const int GetMinimalNotedValue(); 
		const int GetAverageNotedValue(); 

		wxBrush _BRUSH = *wxYELLOW_BRUSH; 
		wxPen _PEN = *wxYELLOW_PEN;

		std::string _UNIT;
		int _INFORESERVED = 28;
		int _STATUSLENGHT = 3;
		int _STATUSSPACING = 1;

		std::chrono::milliseconds _REFRESH = std::chrono::milliseconds(400); 
		bool _LOCKED;
		int _MAXIMAL;
		int (*_STATUS)();
		std::vector<int> Buffer; 
		const std::string _NAME;
		std::vector<int> _BUFFERUNLIMITED;
	};
}