#pragma once
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <filesystem>
#include "../../../Engine/Engine.h"
#include "../../Render/Render.h"

class Cmd : public wxFrame
{
public:
	Cmd(
		const std::string& _NAME, std::filesystem::path _AT
	);

	// 
	// [ STRUCTS ] 
	// 

	enum COMMAND_LINE_MODE
	{
		READ_AND_WRITE = 0
	};

	const std::vector<std::string> ARGUMENT_EMPTY;

	struct COMMAND_STRUCT
	{
	public:

		COMMAND_STRUCT(
			const std::string& NAME, void*(Cmd::*FUNC)(const std::vector<std::string>&)
		) : NAME(NAME), FUNC(FUNC) {
			
		};

		bool Call(
			Cmd* HANDLER, const std::vector<std::string>& ARGUMENTS
		) const {
			try {
				(HANDLER->*FUNC)(ARGUMENTS);
			}
			catch (
				const Engine::Debug::Object& /*Exception*/
				) {
				return false; 
			}
			return true; 
		}

		std::string GetName() const {
			return this->NAME;
		}

	private:
		const std::string NAME; void* (Cmd::*FUNC)(const std::vector<std::string>&);
	};

	// 
	// [ USER_CALLS ] 
	// 
	const void PUBLIC_COMMAND_PUSH(
		Cmd::COMMAND_STRUCT COMMAND
	);

	const void COMMAND_LINE_HANDLE_PUSH_BUFFER_LINE(
		const std::string& BUFFER
	);

private:
	//
	// [ SETUP ] 
	//
	
	// [ _COMMAND_LINE ] 
	const void SETUP_COMMAND_LINE_FONT(
		const std::string& FACENAME, const int& SIZE
	);

	const void SETUP_COMMAND_LINE_DEFAULT_COLOR(
		const int& R, const int& G, const int& B
	);

	const void SETUP_COMMAND_LINE_DIFFERENCE_BETWEEN_EDGES(
		const int& LENGHT, const int& HEIGHT
	);

	const void SETUP_COMMAND_LINE_DIFFERENCE_BETWEEN_LINES(
		const int& DIF
	);

	// [ _COMMAND ] 
	void SETUP_COMMANDS(); 

	// [ _WX ]
	const void SETUP_BINDS();

	// [ _VARIABLES ] 
	const void SETUP_REGISTER_VARIABLES(
		const std::filesystem::path& _AT
	);

	// [ _CONFIG ]
	const void SETUP_CONFIG_HANDLE(
		const std::filesystem::path& _AT
	);

	// [ _STYLE ]
	const void SETUP_BACKGROUND_STYLE(
		const int& r, const int& g, const int& b
	);

	// [ _SIZE ]
	const void SETUP_SIZE(
		const int& DEFAULT_X, const int& DEFAULT_Y
	); 

	// [ _MOUSE_INTERFACE ]
	const void SETUP_MOUSE_INTERFACE_FONT(
		const std::string& FACENAME, const int& SIZE
	);

	const void SETUP_MOUSE_INTERFACE_RESERVED_SPACE(
		const int& FONT_SIZE
	);

	const void SETUP_MOUSE_INTERFACE_ADDITIONAL_RESERVED_SPACE(
		const int& ADDITIONAL
	);

	const void SETUP_MOUSE_INTERFACE_COLORS(
		const int& TEXT_R, const int& TEXT_G, const int& TEXT_B, const int& BACKGROUND_R, const int& BACKGROUND_G, const int& BACKGROUND_B
	);

	// [ _VERTICAL_SLIDER ] 
	const void SETUP_VERTICAL_SLIDER_RESERVED_SPACE(
		const int& SIZE
	); 

	const void SETUP_VERTICAL_SLIDER_COLORS(
		const int& MAIN_R, const int& MAIN_G, const int& MAIN_B, const int& BACKGROUND_R, const int& BACKGROUND_G, const int& BACKGROUND_B
	);

	const void SETUP_VERTICAL_SLIDER_DIFFERENCES(
		const int& X, const int& Y
	);

	// 
	// [ DRAW ] 
	// 

	// [ _COMMAND_LINE ] 
	void COMMAND_LINE_DRAW(
		wxPaintEvent& evt
	); 

	const int COMMAND_LINE_DRAW_GET_MAXIMAL_SCROLL();

	const int COMMAND_LINE_DRAW_GET_SCROLL(
		const float &PROCENTAGE
	);

	const void COMMAND_LINE_DRAW_BUFFER(
		wxPaintDC* dc
	); 

	const void COMMAND_LINE_DRAW_BUFFER_SETUP_DC(
		wxPaintDC* dc
	); 

	const wxPoint COMMAND_LINE_DRAW_GET_STARTING_POSITION();
	const wxPoint COMMAND_LINE_DRAW_GET_FINAL_POSITION();

	const wxSize COMMAND_LINE_DRAW_GET_SIZE();

	// [ _VERTICAL_SLIDER ] 
	void VERTICAL_SLIDER_DRAW(
		wxPaintEvent& evt
	); 

	const void VERTICAL_SLIDER_DRAW_BACKGROUND(
		wxPaintDC* dc
	); 

	const void VERTICAL_SLIDER_DRAW_MAIN(
		wxPaintDC* dc
	); 

	const wxPoint VERTICAL_SLIDER_DRAW_GET_BACKGROUND_POSITION(); 
	const wxSize VERTICAL_SLIDER_DRAW_GET_BACKGROUND_SIZE();

	const wxPoint VERTICAL_SLIDER_DRAW_GET_MAIN_POSITION();
	const wxSize VERTICAL_SLIDER_DRAW_GET_MAIN_SIZE();

	const wxPoint VERTICAL_SLIDER_DRAW_GET_MAIN_STARTING_POSITION(); 
	const wxPoint VERTICAL_SLIDER_DRAW_GET_MAIN_FINAL_POSITION();

	// [ _MOUSE_INTERFACE ]
	const std::vector<std::string> MOUSE_INTERFACE_DRAW_GET_TEXT_VECTOR(); 

	const void MOUSE_INTERFACE_DRAW_UPDATE_TEXT_SIZES(
		wxPaintDC* dc
	);

	void MOUSE_INTERFACE_DRAW(
		wxPaintEvent& evt
	);

	const void MOUSE_INTERFACE_DRAW_BACKGROUND(
		wxPaintDC* dc
	); 

	const void MOUSE_INTERFACE_DRAW_TEXT(
		wxPaintDC* dc
	);

	const void MOUSE_INTERFACE_DRAW_SETUP_TEXT_DC(
		wxPaintDC* dc
	);

	const wxPoint MOUSE_INTERFACE_DRAW_GET_BACKGROUND_POSITION();
	const wxSize MOUSE_INTERFACE_DRAW_GET_BACKGROUND_SIZE();

	const wxPoint MOUSE_INTERFACE_DRAW_GET_TEXT_POSITION(
		wxPaintDC* dc, const std::string& TEXT
	); 

	const std::string MOUSE_INTERFACE_DRAW_GET_TEXT();

	// 
	// [ HANDLE ]  
	//

	// [ _COMMAND_LINE ] 
	const std::vector<std::string> COMMAND_LINE_HANDLE_FORMAT_BUFFER(
		wxPaintDC* dc, const std::vector<std::string>& BUFFER, const int& MAXIMAL_INT
	);

	// [ _HANDLE ? ]
	const void HANDLE_UPDATE(); 

	void HANDLE_RESIZE(
		wxSizeEvent& evt 
	); 

	// [ _MOUSE_INTERFACE ] 
	void MOUSE_INTERFACE_HANDLE_MOUSE_INTERACTION_OPEN(
		wxMouseEvent& evt
	); 

	// [ _MOUSE ]
	void MOUSE_HANDLE_SET_POSITION(
		wxMouseEvent& evt
	);

	// [ _VERTICAL_SLIDER ] 
	void VERTICAL_SLIDER_HANDLE_MOUSE_INTERACTION(
		wxMouseEvent& evt
	); 

	void VERTICAL_SLIDER_HANLE_MOUSE_INTERACTION_START(
		wxMouseEvent& evt 
	); 

	void VERTICAL_SLIDER_HANDLE_MOUSEWHEEL_INTERACTION(
		wxMouseEvent& evt
	); 

	const void VERTICAL_SLIDER_HANDLE_SET_SCROLL(
		const int& SCROL
	);

	const float VERTICAL_SLIDER_HANDLE_GET_SCROLL_PROCENTAGE();

	const int VERTICAL_SLIDER_HANDLE_GET_MAX_SCROLL();

	// [ _COMMANDS ] 

	const void COMMANDS_HANDLE_FIND_AND_CALL(
		const std::string& NAME, const std::vector<std::string>& ARGUMENTS
	); 


	// 
	// [ VARIABLES ] 
	// 

	// [ _COMMAND_LINE ] 
	std::vector<std::string> COMMAND_LINE_ORIGINAL_BUFFER = { "First lineaaaaaaaaaaaaaaaaaaaaaaa12334 lniggs'errrrssssssssssssssss niggers niasdasdasdjsa END", "Second Line" };
	std::vector<std::string> COMMAND_LINE_FORMATED_BUFFER;
	
	std::vector<int> COMMAND_LINE_CURSOR_AT = { 0, 0 };
	
	wxColor COMMAND_LINE_DEFAULT_COLOR;

	std::string COMMAND_LINE_FONT_FACENAME; 
	int COMMAND_LINE_FONT_SIZE;

	int COMMAND_LINE_DIFFERENCE_BETWEEN_LINES;
	wxPoint COMMAND_LINE_DIFFERENCE_BETWEEN_EDGES;

	int COMMAND_LINE_BUFFER_LINE_HEIGHT;

	// [ _VERTICAL_SLIDER ] 
	int VERTICAL_SLIDER_RESERVED_SPACE; 
	
	wxColor VERTICAL_SLIDER_COLOR_BACKGROUND; 
	wxColor VERTICAL_SLIDER_COLOR_MAIN; 

	int VERTICAL_SLIDER_SCROLL = 0; 

	int VERTICAL_SLIDER_MAIN_DIFFERENCE_FROM_BACKGROUND_X; 
	int VERTICAL_SLIDER_MAIN_DIFFERENCE_FROM_BACKGROUND_Y;
	
	int VERTICAL_SLIDER_MAIN_DIFFERENCE_FROM_MOUSE_Y;
	bool VERTICAL_SLIDER_MAIN_INTERACTING = false; 

	// [ _MOUSE_INTERFACE ]

	// _DRAW
	wxPaintDC* MOUSE_INTERFACE_DRAW_DC; 
	std::vector<int> MOUSE_INTERFACE_TEXT_SIZES; 

	// _FONT 
	std::string MOUSE_INTERFACE_FONT_FACENAME; 
	int MOUSE_INTERFACE_FONT_SIZE;

	// _RESERVED_SPACE
	int MOUSE_INTERFACE_RESERVED_SPACE; 
	int MOUSE_INTERFACE_ADDITIONAL_RESERVED_SPACE;

	// _COLORS
	wxColor MOUSE_INTERFACE_COLOR_BACKGROUND;
	wxColor MOUSE_INTERFACE_COLOR_TEXT; 

	// _TEXT
	int MOUSE_INTERFACE_ADDITIONAL_TEXT_X = 10;

	// [ _MOUSE ] 
	wxPoint MOUSE_POSITION = wxPoint(0, 0);

	// [ _COMMAND ] 
	std::vector<Cmd::COMMAND_STRUCT> COMMAND_LIST;

	//_?

	std::filesystem::path& _AT; 
	Engine::Config* Config;

	bool FORCE_UPDATE = false; 

	// 
	// [ _COMMAND's ]
	// 
	Render::Graph* COMMAND_MEMORY_USAGE_GRAPH;

	void* COMMAND_MEMORY_USAGE(
		const std::vector<std::string>&
	); 

	void* COMMAND_SETTINGS(
		const std::vector<std::string>&
	); 

	void* COMMAND_REFRESH(
		const std::vector<std::string>&
	); 
};