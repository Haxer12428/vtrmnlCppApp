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
			void* (*vFunc)(Window*&, CommandArguments), const std::string& AssignedName, const std::vector<std::string> &AssignedHelp 
		) : AssignedFunction(vFunc), AssignedName(AssignedName), AssignedHelp(AssignedHelp)
		{}

		void* AssignedFunction; const std::string AssignedName; std::vector<std::string> AssignedHelp;
	};

	void PushBufferInVector(
		const std::vector<std::string>& buffer
	);

	void PushBuffer(
		const std::string& buffer
	);

	const std::vector<CommandFunc>& GetTerminalAssignedCommands();

	void NewLine();

	void PushCommand(
		void* (*vFunc)(Window*&, CommandArguments), const std::string& vFuncName, const std::vector<std::string> &CommandHelpBuffer
	);

	void RunHistory(
		const int& position
	);

	void ClearTerminalBuffer();

	std::vector<std::string> GetTerminalCommandHistoryBuffer(
		const size_t &lenght = INT64_MAX
	);

private:
	//Vars 
	std::vector <
		std::string> TerminalCommandHistoryBuffer;

	std::vector<
		CommandFunc> TerminalAssignedCommands;

	std::vector<
		std::string> TerminalBuffer = {};

	wxScrollBar* VerticalScrollbar;

	wxCoord BufferScrollAmount = 0;
	wxCoord BufferLineHeight = 0;

	std::string UserInputBuffer = "";

	long BufferPushCount = 0;
	float BufferScrollOnLastUpdate = 0; 

	//Render

	void RenderText(
		wxPaintEvent& evt
	);

	void RenderCursor(
		wxPaintDC& paint
	);

	void RenderVerticalScrollbar();

	//Handle 
	void InitializeBuffer();

	void UpdateHistoryBuffer(
		const std::string& Buffer
	);

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

	void HandleVerticalScrollbarOnMouseWheelMovement(
		wxMouseEvent& evt
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

