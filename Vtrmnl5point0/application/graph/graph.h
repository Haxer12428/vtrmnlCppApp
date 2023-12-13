#pragma once
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <chrono>
#include <thread>

class graph : public wxFrame
{
public:
	graph(
		wxFrame* parent, const std::string& name, const int& maximal_value, const std::string& unit
	); 

	const void assign_function(
		int (*function)()
	);

	const int get_maximal_buffer();
	const int get_minimal_buffer();
	const int get_average_buffer(); 

private:
	//draw
	void draw(
		wxPaintEvent& evt
	); 

	const void draw_background(
		wxAutoBufferedPaintDC& paint
	);
	const void draw_status_info(
		wxAutoBufferedPaintDC& paint
	); 
	const void draw_buffer(
		wxAutoBufferedPaintDC& paint
	); 
	const void draw_update_name(); 

	//setup 
	void setup_binds(); 

	//handle
	const void handle_update_buffer();
	const void handle_buffer(); 
	const void handle_limit_buffer(); 
	

	//vars 
	int buffer_draw_spacing = 1; 
	int buffer_draw_lenght = 3; 


	wxColor buffer_color_default = wxColor(0, 180, 255);
	wxColor buffer_color_medium = wxColor(0, 255, 0);
	wxColor buffer_color_high = wxColor(255, 0, 0);

	int status_info_reserved_space = 40; 
	wxColor status_info_color = wxColor(255, 255, 255);

	std::chrono::milliseconds refresh_rate = std::chrono::milliseconds(400);

	int (*assigned_function)(); 

	int maximal_value;

	std::string name; 

	std::vector<int> buffer; 

	std::string unit; 
};