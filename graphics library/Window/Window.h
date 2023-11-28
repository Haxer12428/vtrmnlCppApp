#pragma once
#include <wx/wx.h>
#include "../Config/Config.h"
#include <functional>

class Window : public wxFrame
{
public:
	Window(const wxString& name);

	struct CommandArguments
	{
	public:
		CommandArguments(
			const std::string& fName, std::vector<std::string> aList
		) : FunctionName(fName), List(aList) {

		}

		const std::string FunctionName;

		std::vector<
			std::string> List;
	};

	struct CommandFunc
	{
	public:
		CommandFunc(
			void* (*vFunc)(Window*&, CommandArguments), const std::string& AssignedName
		) : AssignedFunction(vFunc), AssignedName(AssignedName)
		{}

		void* AssignedFunction; const std::string AssignedName;
	};

	void PushBuffer(
		const std::string& buffer
	);

	void NewLine();

	void PushCommand(
		void* (*vFunc)(Window*&, CommandArguments), const std::string& vFuncName
	);

	void ClearTerminalBuffer();

private:
	//Vars 
	std::vector<
		CommandFunc> TerminalAssignedCommands;

	std::vector<
		std::string> TerminalBuffer = {};

	wxScrollBar* VerticalScrollbar;

	wxCoord BufferScrollAmount = 0;
	wxCoord BufferLineHeight = 0;

	std::string UserInputBuffer = "";

	long BufferPushCount = 0;

	//Render

	void RenderText(
		wxPaintEvent& evt
	);

	void RenderCursor(
		wxPaintDC& paint
	);

	void RenderVerticalScrollbar();

	//Handle 
	void HandleBufferScrollIdle(
		wxIdleEvent& evt
	);

	void HandleVerticalScrollbar(
		wxScrollEvent& evt 
	);

	void HandleBufferRefresh();

	void HandleBufferPushIdle(
		wxIdleEvent& evt
	);

	void HandleUserBufferInput(
		wxKeyEvent& evt
	);

	void HandleAnalzyeAndAwakeUserPush(
		std::string InputBuffer
	);

	void HandleBufferPush();

	//Help
	float GetMaximalBufferScroll();
	bool CanScrollBuffer();
	void MaxBufferScroll();

	void DeleteUserInput();

	void ChangeUserInput(
		char Keycode
	);

	void EnterUserInput();

	CommandArguments GetArgumentsFromString(
		std::string &string 
	);

	const std::string GetSimiliarCommands(
		const std::string& command
	);


	//Config 
	
	class LoadConfig
	{
	public: 
		LoadConfig(
			Window* WindowPtr
		);

		void PrepareConfig(
			std::filesystem::path &ConfigPath
		);

	private:
		void LoadWxFrameSize();
		void LoadWxFrameBackground();

		Window* WindowPtr;
		Config* ConfigSystem;
	};

	
};

