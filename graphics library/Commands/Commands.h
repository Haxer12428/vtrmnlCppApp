#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <string>
#include <thread>
#include "../Window/Window.h"
#include "../sdl/sdl.h"
#include "../Monitor/Graph.h"

class Commands 
{
public:

	static void* History(Window*& Obj, Window::CommandArguments);

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

			std::filesystem::path BufferFilepath = Commands::AddRoute(Buffer.substr(6));

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

	static void* HistoryManualSwitch(Window*& Obj, Window::CommandArguments Arguments);

	static void* NetOpenBrowserURL(Window*& Obj, Window::CommandArguments Arguments);

	static void* Help(Window*& Obj, Window::CommandArguments);

	static void* Move(Window*& Obj, Window::CommandArguments);

	static void* Route(Window*& Obj, Window::CommandArguments);

	//static void* Ping(Window*& Obj, Window::CommandArguments Arguments);

	static void* fCopy(Window*& Obj, Window::CommandArguments Arguments);

	static void* List(Window*& Obj, Window::CommandArguments Arguments);

	static void* MemoryTotal(Window*& Obj, Window::CommandArguments Arguments);

	static void* MemoryMonitorUsage(Window*& Obj, Window::CommandArguments Arguments);

	static void* CPUMonitorUsage(
		Window*& Obj, Window::CommandArguments Arguments
	);
	static void* MemoryMonitorUsageSelf(
		Window*& Obj, Window::CommandArguments Arguments
	);

	static void* CPUMonitorFrequency(
		Window*& Obj, Window::CommandArguments Arguments
	);

	Commands(Window*& Window);

	static const std::filesystem::path AddRoute(
		const std::filesystem::path& Path
	);

private:

	Window* WindowObject;
};