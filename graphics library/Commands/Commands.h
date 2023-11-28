#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <string>
#include <thread>
#include "../Window/Window.h"

class Commands 
{
public:

	static void* Clear(Window*& Obj, Window::CommandArguments);

	static void* RecursiveFolderFileList(Window*& Obj, Window::CommandArguments Arguments);

	static void* Start(Window*& Obj, Window::CommandArguments Arguments);

	static void* Echo(Window*& Obj, Window::CommandArguments Arguments)
	{
		if (
			Arguments.List.size() == 0
			) {
			Obj->PushBuffer("static void* Commands::Echo -> Function terminated, incorrect amount of arguments; Expected: 1"); return 0;
		}

		const std::string Buffer = Arguments.List[0];

		if (
			Buffer.find("_FILE:") == 0
			) {
			Obj->NewLine(); Obj->PushBuffer("`PRINT_MODE: _FILE"); 

			std::filesystem::path BufferFilepath = Buffer.substr(6);

			Obj->PushBuffer(
				"`PATH: " + BufferFilepath.string()
			); 
			
			Obj->NewLine();

			if (
				!std::filesystem::is_regular_file(BufferFilepath)
				) {
				Obj->PushBuffer("static void* Echo -> Function terminated, file doesn't exist."); return 0;
			}

			std::string CurrentFileBuffer; std::fstream File; File.open(
				BufferFilepath, std::ios::in
			);

			do {
				Obj->PushBuffer(CurrentFileBuffer);

			} while (std::getline(File, CurrentFileBuffer));

			Obj->NewLine();
			return 0; 
		}

		Obj->PushBuffer(Arguments.List[0]); return 0;
	}

	Commands(Window*& Window);


private:

	Window* WindowObject;
};