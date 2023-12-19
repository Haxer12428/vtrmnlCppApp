#pragma once
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include "../../engine/engine.h"
#include "../graph/graph.h"

class frame : public wxFrame {
public:
	// [ 
	//   CONSTRUCTOR 
	// ] 

	frame(const std::string& name);

	// [ 
	//   STRUCT's
	// ] 

	// [ COMMAND_LINE_DRAW_TEXT ] 

	struct draw_command_line_colored_text {
		std::string text;
		std::string color_hex;
	};

	// [ COMMAND_LINE_BUFFER_INPUT ] 

	enum command_line_buffer_input_mode {
		write = 0, 
		read = 1
	};

	// [ ASSIGNED_FUNCTION ] 

		const std::vector<std::string> argument_empty = {};

		struct assigned_function
		{
		public:
			assigned_function(
				void* (frame::* function)(const std::vector<std::string> &arguments), const std::string& name
			);

			const bool call(
				frame* obj, const std::vector<std::string> &arguments
			) const;

			const std::string get_name() const; 

		private:
			void* (frame::*function)(
				const std::vector<std::string>&
				); 
			const std::string name; 
		};

		const void assigned_function_push(
			const frame::assigned_function& assigned
		);

		const bool assigned_function_find_and_call(
			const std::string& name, const std::vector<std::string>& arguments
		); 
	// [ COMMAND_LINE ] 
		// [ BUFFER ] 
		const void handle_command_line_buffer_push_line(
			const std::string& buffer
		); 

	// ...

private:
	// [ 
	//   SETUP 
	// ]

	// [ CONFIG ] 

		engine::config* config = new engine::config("C:\\Vtrmnl\\6\\config.cfg");

		// [ MAIN ] 
			const void setup_config(); 
			// [ STYLE ] 
				const void setup_style();
			// [ BACKGROUND ] 
				const void setup_frame_draw_background_color();
			// [ MOUSE_INTERACTIVE_PANEL ] 
				const void setup_mouse_interactive_panel(); 

				// [ ASSIGNED_FUNCTIONS ] 
					const void setup_mouse_interactive_panel_assigned_functions();

			// [ VERTICAL_SLIDER ] 
				const void setup_vertical_scrollbar(); 
			// [ COMMAND_LINE ] 
				const void setup_command_line(); 

				// [ ASSIGNED_FUNCTIONS ] 
					const void setup_command_line_assigned_functions(); 
		//... 

	// [ BINDS ] 
		const void setup_binds(); 

	// [ 
	//   DRAW 
	// ]
	
	void draw(
		wxPaintEvent& evt
	);

	// [ HELP ] 
	const wxColor draw_help_color_hex_to_rgb(
		const std::string& clr_str
	) const;

	// [ BACKGROUND ] 
		const void frame_draw_background(
			wxAutoBufferedPaintDC& dc
		);
	// [ COMMAND_LINE ] 
		// [ DRAW ] 
			const void draw_command_line(
				wxAutoBufferedPaintDC& dc
			);
			// [ TEXT ] 
				const void draw_command_line_text(
					wxAutoBufferedPaintDC& dc
				);
			// [ CURSOR ] 
				const void draw_command_line_cursor(
					wxAutoBufferedPaintDC& dc
				); 

		// [ SUB_FUNCTIONS ] 
			// [ CURSOR ] 
				const wxPoint draw_command_line_cursor_help_get_starting_position(
					const std::vector<int> in_buffer_position, wxAutoBufferedPaintDC& dc
				); 

				const wxSize draw_command_line_cursor_help_get_size(
					const std::vector<int> in_buffer_position, wxAutoBufferedPaintDC& dc
				);
			// [ TEXT ] 
				const wxPoint draw_command_line_text_help_get_starting_position(); 
				const wxPoint draw_command_line_text_help_get_final_position(); 

				const int draw_command_line_text_help_get_text_line_height(
					wxAutoBufferedPaintDC& dc
				); 

				const wxPoint draw_command_line_text_help_get_current_line_position(
					wxAutoBufferedPaintDC& dc, const int buffer_iterator 
				); 

				const wxSize draw_command_line_text_help_get_area_size();

				const std::vector<frame::draw_command_line_colored_text> draw_command_line_text_help_parse_text_with_color_from_string(
					const wxString& buffer
				) const;

	// [ VERTICAL_SCROLLBAR ] 
		// [ DRAW ] 
			const void draw_vertical_scrollbar(
				wxAutoBufferedPaintDC& dc
			); 
			// [ BACKGROUND ] 
				const void draw_vertical_scrollbar_background(
					wxAutoBufferedPaintDC& dc
				); 

			// [ MOVABLE ] 
				const void draw_vertical_scrollbar_movable(
					wxAutoBufferedPaintDC& dc
				); 
		// [ SUB_FUNCTIONS ] 
			// [ BACKGROUND ] 
				const wxPoint draw_vertical_scrollbar_help_get_background_starting_position(); 
				const wxPoint draw_vertical_scrollbar_help_get_background_final_position(); 

				const wxSize draw_vertical_scrollbar_help_get_background_size(); 
			// [ MOVABLE ] 
				const wxPoint draw_vertical_scrollbar_help_get_movable_starting_position(); 
				const wxPoint draw_vertical_scrollbar_help_get_movable_final_position(); 
				
				const wxSize draw_vertical_scrollbar_help_get_movable_size(); 

				const wxPoint draw_vertical_scrollbar_help_get_movable_current_position(); 

				const int draw_vertical_scollbar_help_get_maximal_scroll();

				const float draw_vertical_scrollbar_help_get_movable_scroll_procentage(); 
	// [ MOUSE_INTERACTIVE_PANEL ] 
		// [ DRAW ]
			const void draw_mouse_interactive_panel_main(
				wxAutoBufferedPaintDC& dc
			);
			// [ TEXT | BUFFER ] 
				const void draw_mouse_interactive_panel_text(
					wxAutoBufferedPaintDC& dc
				);
			// [ BACKGROUND ] 
				const void draw_mouse_interactive_panel_background(
					wxAutoBufferedPaintDC& dc
				);


		// [ SUB_FUNCTIONS ] 
			const wxPoint draw_mouse_interactive_panel_get_starting_position() const;
			const void draw_mouse_interactive_panel_update_reserved_space_total();
			const std::vector<std::string> draw_mouse_interactive_panel_get_text_vector() const;
			const std::string draw_mouse_interactive_panel_get_text_string() const;
		//...
	
	// [ 
	//   HANDLE 
	// ] 
		
	// [ RESIZE ] 
		void handle_resize(
			wxSizeEvent& evt
		); 

		void handle_resize_after(
			wxIdleEvent& evt
		);
	// [ COMMAND_LINE ] 
		// [ BUFFER ] 
			const void handle_command_line_buffer_format(
				const std::vector<std::string>& buffer, const int &maximal_lenght_x
			);
		// [ INPUT ] 
			frame::command_line_buffer_input_mode handle_command_line_buffer_input_mode = frame::command_line_buffer_input_mode::write;

			std::string handle_command_line_buffer_input_cache = ""; // empty str 

			void handle_command_line_buffer_input(
				wxKeyEvent& evt
			);

			const void handle_command_line_buffer_input_awake_assigned_function(
				const std::string& input
			); 

			const std::vector<std::string> handle_command_line_buffer_input_help_get_arguments(
				const std::string& input
			) const; 

	// [ MOUSE_INTERACTIVE_PANEL ] 
		// [ INTERACTION ] 
			void handle_mouse_interactive_panel_interaction(
				wxMouseEvent& evt
			);

	// [ VERTICAL_SCROLLBAR ] 
		// [ INTERACTION ] 
			void handle_vertical_scrollbar_interaction(
				wxMouseEvent& evt
			); 

			void handle_vertical_scrollbar_interaction_start(
				wxMouseEvent& evt
			);
		// [ RESIZE ] 
			void handle_vertical_scrollbar_resize(
				wxSizeEvent& evt
			);

	// [ 
	//   VARIABLES 
	// ]

	// [ HANDLE_RESIZE ] 
		bool handle_resize_after_resizing = true; 
	// [ VERTICAL_SCROLLBAR ] 
		// [ BACKGROUND ] 
			// [ SPACING ] 
				int draw_vertical_scrollbar_background_reserved_space; 
			// [ COLORS ] 
				wxColor draw_vertical_scrollbar_background_color; 
		// [ MOVABLE ] 
			// [ SPACING ] 
				double draw_vertical_scrollbar_movable_size_factor_y = .33; 
				double draw_vertical_scrollbar_movable_size_factor_x = .5; 
					
				int draw_vertical_scrollbar_movable_area_dif; 
			// [ SCROLL ] 
				int draw_vertical_scrollbar_movable_scroll_amount = 0; 
				int draw_vertical_scrollbar_movable_scroll_dif = 0; 
			
				bool handle_vertical_scrollbar_in_drag = false; 
			// [ COLORS ] 
				wxColor draw_vertical_scrollbar_movable_color; 
	
	// [ MOUSE_INTERACTIVE_PANEL ]
		// [ TEXT ] 
			// [ SPACING | RESERVED_SPACE ]
				int draw_mouse_interactive_panel_reserved_space_total;
				int draw_mouse_interactive_panel_reserved_space_user_extension;

				int draw_mouse_interactive_panel_spacing_between_text;

				int draw_mouse_interactive_panel_text_user_push_x;
			// [ FONT ] 
				std::string draw_mouse_interactive_panel_font_facename; 
				int draw_mouse_interactive_panel_font_size;

				wxFont draw_mouse_interactive_panel_font;
		// [ BACKGROUND ] 
			wxColor draw_mouse_interactive_panel_background_color;

	// [ COMMAND_LINE ] 
		// [ CURSOR ] 
			std::vector<int> draw_command_line_cursor_position_in_buffer = { -1, 1 }; // line|char 

			// colors 
			wxColor draw_command_line_cursor_color; 
		// [ TEXT ] 
			// [ FONT ] 
				std::string draw_command_line_font_facename; 
				int draw_command_line_font_size; 

				wxFont draw_command_line_font; 
			// [ SPACING ]
				int draw_command_line_text_push_x; 
				int draw_command_line_text_push_y; 

				int draw_command_line_text_spacing;
			// [ BUFFER ] 
			int draw_command_line_buffer_scroll = 0; 

			std::vector<std::string> draw_command_line_buffer_original;
			std::vector<std::string> draw_command_line_buffer_formated;

	// [ BACKGROUND ] 
		wxColor frame_draw_background_color;

	// [ ASSIGNED_FUNCTIONS ] 
		std::vector<frame::assigned_function> assigned_functions;
		
		// [ FUNCTIONS ] 
			// [ MOUSE_INTERACTIVE_PANEL_MEMORY_USAGE ] 
				graph* assigned_function_mouse_interactive_panel_memory_usage_graph;

				void *assigned_function_mouse_interactive_panel_memory_usage(
					const std::vector<std::string>&
				);
			// [ COMMAND_LINE_GET_FILES ] 
				const void assigned_function_command_line_get_files_recursive(
					const std::filesystem::path& path
				); 

				const void assigned_function_command_line_get_files_non_recursive(
					const std::filesystem::path& path
				); 

				void* assgined_function_command_line_get_files(
					const std::vector<std::string>& arguments 
				);
			// [ COMMAND_LINE_SYSTEM32_SHUTDOWN ] 
				void* assigned_function_command_line_system32_shutdown(
					const std::vector<std::string>& arguments
				);
			// [ COMMAND_LINE_SYSTEM32_PROCESS_KILL ] 
				void* assigned_function_comand_line_system32_process_memory_usage(
					const std::vector<std::string>& arguments
				);
			// [ COMMAND_LINE_TERMINAL_ClEAR_BUFFER 
				void* assigned_function_command_line_terminal_clear_buffer(
					const std::vector<std::string>& arguments
				); 
};