#include "Window.h"

//Window _INIT

Window::Window(
	const wxString& name
) : wxFrame(nullptr, wxID_ANY, name) {
	Window::LoadConfig(this);

	wxPanel* Panel = new wxPanel(this);
	Panel->Show(false);

	this->RenderVerticalScrollbar();
	//this->Bind(wxEVT_PAINT, &Window::RenderCursor, this);
	this->Bind(wxEVT_PAINT, &Window::RenderText, this);
	this->Bind(wxEVT_IDLE, &Window::HandleBufferPushIdle, this);
	this->Bind(wxEVT_CHAR, &Window::HandleUserBufferInput, this);
	this->Bind(wxEVT_IDLE, &Window::HandleBufferScrollIdle, this);
	this->Bind(wxEVT_MOUSEWHEEL, &Window::HandleVerticalScrollbarOnMouseWheelMovement, this);

	this->HandleBufferRefresh();
	this->InitializeBuffer();

	this->Show();
}

//PUBLIC

const std::vector<Window::CommandFunc>& Window::GetTerminalAssignedCommands()
{
	return this->TerminalAssignedCommands;
}

void Window::PushBufferInVector(
	const std::vector<std::string>& buffer
) {
	for (
		const std::string& bufferFraction : buffer
		) this->PushBuffer(bufferFraction);
}

void Window::RunHistory(
	const int& position
) {

	if (
		this->TerminalCommandHistoryBuffer.size() == 0
		) throw std::exception("Window::RunHistory -> Function terminated. History buffer is empty."); 

	if (
		this->TerminalCommandHistoryBuffer.size() <= std::abs(position)
		) {
		throw std::exception("Window::RunHistory -> Function terminated, position is out of buffer bounds.");
	}

	if (
		position < 0
		) {
		const std::string& Buffer = this->TerminalCommandHistoryBuffer[this->TerminalCommandHistoryBuffer.size() - std::abs(position) - 1];

		if (
			Buffer.length() != 0 && std::string(1, Buffer.at(0)) == "!"
			) throw std::exception("Window::RunHistory -> Function terminated, running this command in loopback may cause memory leaks.");

		this->HandleAnalzyeAndAwakeUserPush(Buffer);
		return; 
	}

	const std::string& Buffer = this->TerminalCommandHistoryBuffer[position];

	if (
		Buffer.length() != 0 && std::string(1, Buffer.at(0)) == "!" 
		) throw std::exception("Window::RunHistory -> Function terminated, running this command in loopback may cause memory leaks.");

	this->HandleAnalzyeAndAwakeUserPush(Buffer);
}

std::vector<std::string> Window::GetTerminalCommandHistoryBuffer(
	const size_t& lenght
) {
	std::vector<std::string> ResizedHistoryBuffer; 

	if (
		this->TerminalCommandHistoryBuffer.size() <= lenght || lenght == -1
		) return this->TerminalCommandHistoryBuffer;

	for (
		size_t HistoryIterator = 1; HistoryIterator <= lenght; HistoryIterator++
		) {
		ResizedHistoryBuffer.push_back(this->TerminalCommandHistoryBuffer[
			this->TerminalCommandHistoryBuffer.size() - HistoryIterator
		]);
	} return ResizedHistoryBuffer;
}

void Window::PushCommand(
	void* (*vFunc)(Window*&, CommandArguments), const std::string& vFuncName, const std::vector<std::string> &CommandHelpBuffer
) {
	this->TerminalAssignedCommands.push_back(
		Window::CommandFunc(vFunc, vFuncName, CommandHelpBuffer)
	);
}

void Window::PushBuffer(
	const std::string& buffer
) {
	this->TerminalBuffer.push_back(
		buffer
	); this->BufferPushCount++; this->HandleBufferPush();
}

void Window::NewLine()
{
	this->PushBuffer("");
}

void Window::ClearTerminalBuffer()
{
	this->TerminalBuffer = {}; 
}

//_HELP

void Window::ChangeUserInput(
	char KeyChar
) {
	size_t TerminalBufferSize = this->TerminalBuffer.size();

	if (
		TerminalBufferSize == 0
		) {
		this->PushBuffer("$ ");  TerminalBufferSize++;
	};

	this->TerminalBuffer[
		TerminalBufferSize - 1
	] += KeyChar;

	this->UserInputBuffer += KeyChar;

	this->Refresh(); this->Update();
}

const std::string Window::GetSimiliarCommands(
	const std::string& SimiliarTo
) {
	std::string SimiliarCommands = "";

	for (
		Window::CommandFunc& CommandStruct : this->TerminalAssignedCommands
		) {
		if (
			CommandStruct.AssignedName.find(SimiliarTo) != -1
			) {
			SimiliarCommands += CommandStruct.AssignedName + ", ";
		}
	}; if (SimiliarCommands.length() != 0) SimiliarCommands.resize(SimiliarCommands.length() - 2);

	return SimiliarCommands;
}

Window::CommandArguments Window::GetArgumentsFromString(
	std::string& Buffer
) {
	if (
		Buffer.find(" ") == -1
		) return Window::CommandArguments(Buffer, std::vector<std::string>());

	std::string FunctionName; std::vector<std::string> ArgBuffer;

	std::string CurrentArgumentAnalistics = ""; bool InModifyArgument = false;

	for (
		size_t BufferIterator = 0; BufferIterator < Buffer.length(); BufferIterator++
		) {
		std::string BufferChar(1, Buffer.at(BufferIterator));

		if (BufferChar != " " && FunctionName.length() == 0
			) {
			CurrentArgumentAnalistics += BufferChar;
		}

		if ((BufferChar == " " || BufferIterator == Buffer.length() - 1) && FunctionName.length() == 0
			) {
			FunctionName = CurrentArgumentAnalistics; CurrentArgumentAnalistics = "";
		}

		if (
			FunctionName.length() != 0
			) {
			if (
				BufferChar == "\""
				) {
				if (
					InModifyArgument == true
					) {
					InModifyArgument = false; ArgBuffer.push_back(
						CurrentArgumentAnalistics
					);
				}
				else {
					InModifyArgument = true; CurrentArgumentAnalistics = "";
				}
			}
			else if (
				InModifyArgument
				) {
				CurrentArgumentAnalistics += BufferChar;
			}
		}
	}

	return Window::CommandArguments(FunctionName, ArgBuffer);
}

void Window::MaxBufferScroll()
{
	if (
		!this->CanScrollBuffer()
		) return;

	this->BufferScrollAmount = this->GetMaximalBufferScroll();
	
	std::thread LateVerticalSliderUpdate([&] {
		std::this_thread::sleep_for(std::chrono::milliseconds(300)); this->VerticalScrollbar->SetThumbPosition(INT32_MAX);
		}); 
	LateVerticalSliderUpdate.detach();
}

float Window::GetMaximalBufferScroll()
{
	return (float(this->BufferLineHeight) * float(this->TerminalBuffer.size() + 1)) - float(this->GetClientSize().y);
}

bool Window::CanScrollBuffer()
{
	return this->GetMaximalBufferScroll() > 0;
}


//_HANDLE

void Window::HandleVerticalScrollbarOnMouseWheelMovement(
	wxMouseEvent& evt
) {
	int MouseRotation = evt.GetWheelRotation();

	this->VerticalScrollbar->SetThumbPosition(
		this->VerticalScrollbar->GetThumbPosition() - MouseRotation
	);

	this->BufferScrollAmount = this->VerticalScrollbar->GetThumbPosition();
}

void Window::InitializeBuffer()
{
	this->PushBuffer("$ "); this->Refresh(); this->Update();
}

void Window::UpdateHistoryBuffer(
	const std::string& Buffer
) {
	this->TerminalCommandHistoryBuffer.push_back(
		Buffer
	);
}

void Window::HandleAnalzyeAndAwakeUserPush(
	std::string Buffer
) {
	this->UpdateHistoryBuffer(Buffer);
	
	Window::CommandArguments Arguments = this->GetArgumentsFromString(Buffer);


	for (
		Window::CommandFunc& fStruct : this->TerminalAssignedCommands
		)
	{
		if (
			fStruct.AssignedName == Arguments.FunctionName
			)
		{
			Window* wptr = this;

			if (
				Arguments.List.size() != 0 && Arguments.List[0] == "?"
				) {
				this->PushBufferInVector(fStruct.AssignedHelp); return;
			}

			try {
				void(*FunctionReinterpreted)(Window*&, CommandArguments) = reinterpret_cast<void(*)(Window*&, CommandArguments)>(fStruct.AssignedFunction);
				
				FunctionReinterpreted(
					wptr, Arguments
				);
			}
			catch (
				const std::exception& ex
				) {
				this->PushBuffer("void Window::HandleAnalyzeAndAwakeUserPush -> Handled unexpected std::exception: " + std::string(ex.what())); return;
			}

			return;
		}
	};

	this->PushBuffer("There is no such commmand as " + Arguments.FunctionName + ", similiar commands: " + this->GetSimiliarCommands(Arguments.FunctionName));
}

void Window::EnterUserInput()
{
	HandleAnalzyeAndAwakeUserPush(this->UserInputBuffer);
	this->UserInputBuffer = ""; this->PushBuffer("$ ");
}

void Window::DeleteUserInput()
{
	if (
		this->TerminalBuffer.size() == 0
		) return;

	std::string TerminalBufferLastLine = this->TerminalBuffer[
		this->TerminalBuffer.size() - 1
	];

	if (
		TerminalBufferLastLine.length() == 0
		) return;

	if (
		this->UserInputBuffer.length() == 0
		) return;

	this->UserInputBuffer.resize(
		this->UserInputBuffer.length() - 1);

	this->TerminalBuffer[
		this->TerminalBuffer.size() - 1
	].resize(
		this->TerminalBuffer[
			this->TerminalBuffer.size() - 1
		].length() - 1);

		this->Refresh(); this->Update();
}

void Window::HandleUserBufferInput(
	wxKeyEvent& evt
) {
	int Keycode = evt.GetKeyCode();
	char KeycodeChar = Keycode;

	if (
		Keycode == WXK_DELETE || Keycode == WXK_BACK
		) {
		this->DeleteUserInput(); return;
	}

	if (
		Keycode == WXK_NUMPAD_ENTER || Keycode == WXK_RETURN
		) {
		this->EnterUserInput(); return;
	}

	this->ChangeUserInput(
		KeycodeChar
	);
}

void Window::HandleBufferPushIdle(
	wxIdleEvent& evt
) {
	this->VerticalScrollbar->SetRange(this->GetMaximalBufferScroll());
	this->VerticalScrollbar->SetThumbSize(1);

	evt.Skip();
}

void Window::HandleBufferScrollIdle(
	wxIdleEvent& evt
) {
	if (
		this->CanScrollBuffer()
		) {
		evt.Skip(); return;
	}

	this->BufferScrollAmount = 0;

	evt.Skip();
}

void Window::HandleBufferRefresh() {

	std::thread Refresh([&]
		{
			while (
				true
				)
			{
				if (
					BufferPushCount != 0
					) {
					this->Refresh(); this->Update(); BufferPushCount = 0; this->HandleBufferPush();
				}

				if (
					this->BufferScrollOnLastUpdate != this->BufferScrollAmount
					) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					this->Refresh(); this->Update(); this->BufferScrollOnLastUpdate = this->BufferScrollAmount;
				}
			
			}
		});
	Refresh.detach();
}

void Window::HandleBufferPush()
{
	
	this->MaxBufferScroll();
}


void Window::HandleVerticalScrollbar(
	wxScrollEvent& evt
) {
	if (
		!this->CanScrollBuffer()
		) {
		this->BufferScrollAmount = 0;
	}

	float ScrollbarThumbPosition = float(this->VerticalScrollbar->GetThumbPosition());
	float ScrollCalculated = (ScrollbarThumbPosition);

	bool IsScrollDiffrent = wxCoord(ScrollCalculated) != this->BufferScrollAmount;

	if (
		!IsScrollDiffrent
		) return;

	this->BufferScrollAmount = wxCoord(ScrollCalculated);// this->Update(); this->Refresh();
}

//_RENDER

void Window::RenderVerticalScrollbar()
{

	this->VerticalScrollbar = new wxScrollBar(
		this, wxID_ANY, wxPoint(0, 0), wxDefaultSize, wxSB_VERTICAL
	);

	this->VerticalScrollbar->SetScrollbar(0, 50, 100, 1, true);

	wxBoxSizer* VerticalSizer = new wxBoxSizer(wxVERTICAL);
	
	VerticalSizer->Add(this->VerticalScrollbar, wxSizerFlags().Proportion(1).Right());
	this->SetSizer(VerticalSizer);

	this->VerticalScrollbar->Bind(wxEVT_SCROLL_THUMBTRACK, &Window::HandleVerticalScrollbar, this);
}

void Window::RenderText(
	wxPaintEvent& evt
) {
	wxPaintDC Paint(this);

	wxFont Font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_HEAVY);
	Font.SetFaceName("Hack");

	Paint.SetFont(
		Font
	);

	this->RenderCursor(Paint);
	wxCoord HeightDif = 3; wxCoord TextHeight = Paint.GetTextExtent("TextLine").y;
	
	this->BufferLineHeight = (TextHeight + HeightDif);

	for (
		int iBuffer = 0; iBuffer < this->TerminalBuffer.size(); iBuffer++
		)
	{
		std::string Buffer = this->TerminalBuffer[
			iBuffer
		];

		wxPoint cPos = wxPoint(0, (HeightDif + TextHeight) * iBuffer - this->BufferScrollAmount);

		Paint.SetTextForeground(*wxBLACK);
		Paint.DrawText(Buffer, cPos + wxPoint(2, 2));

		if (
			Buffer.length() != 0 && std::string(1, Buffer.at(0)) == std::string("$")
			) {

			Paint.SetTextForeground(*wxLIGHT_GREY);
			Paint.DrawText("$", cPos);

			Paint.SetTextForeground(*wxYELLOW);
			Paint.DrawText(Buffer.substr(1), cPos + wxPoint(Paint.GetTextExtent("$").x, 0));
		}
		else {
			Paint.SetTextForeground(*wxYELLOW);
			Paint.DrawText(Buffer, cPos);
		}
	}
	

}

void Window::RenderCursor(
	wxPaintDC &Paint
) {

	if (
		this->TerminalBuffer.size() == 0
		) return;
	
	int TextLenght = Paint.GetTextExtent(this->TerminalBuffer[this->TerminalBuffer.size() - 1]).x;

	wxCoord BufferLineHeight = this->BufferLineHeight;

	wxPoint CursorPosition = wxPoint(TextLenght, BufferLineHeight * (this->TerminalBuffer.size() - 1) - this->BufferScrollAmount);

	Paint.DrawRectangle(CursorPosition, wxSize(15, BufferLineHeight));
}
