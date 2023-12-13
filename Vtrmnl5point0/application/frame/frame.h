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
		//... 

	// [ BINDS ] 
		const void setup_binds(); 

	// [ 
	//   DRAW 
	// ]
	
	void draw(
		wxPaintEvent& evt
	);

	// [ BACKGROUND ] 
		const void frame_draw_background(
			wxAutoBufferedPaintDC& dc
		);
	// [ VERTICAL_SCROLLBAR ] 
		// [ DRAW ] 
			const void draw_vertical_scrollbar(
				wxAutoBufferedPaintDC& dc
			); 
			// [ BACKGROUND ] 
				const void draw_vertical_scrollbar_background(
					wxAutoBufferedPaintDC& dc
				); 
		// [ SUB_FUNCTIONS ] 
			// [ BACKGROUND ] 
				const wxPoint draw_vertical_scrollbar_help_get_background_starting_position(); 
				const wxPoint draw_vertical_scrollbar_help_get_background_final_position(); 

				const wxSize draw_vertical_scrollbar_help_get_background_size(); 
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

	// [ MOUSE_INTERACTIVE_PANEL ] 
		// [ INTERACTION ] 
			void handle_mouse_interactive_panel_interaction(
				wxMouseEvent& evt
			);

	// [ 
	//   VARIABLES 
	// ]

	// [ VERTICAL_SCROLLBAR ] 
		// [ BACKGROUND ] 
			// [ SPACING ] 
				int draw_vertical_scrollbar_background_reserved_space; 
			// [ COLORS ] 
				wxColor draw_vertical_scrollbar_background_color; 
		// [ MOVABLE ] 
			// [ SPACING ] 
				float draw_vertical_scrollbar_movable_size_factor; 
				int draw_vertical_scrollbar_movable_area_dif; 
			// [ SCROLL ] 
				int draw_vertical_scrollbar_movable_scroll_amount = 0; 
			
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


};