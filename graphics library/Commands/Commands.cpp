#include "Commands.h"

void* Commands::Clear(Window*& Obj, Window::CommandArguments)
{
	Obj->ClearTerminalBuffer(); return 0;
}

void* Commands::RecursiveFolderFileList(Window*& Obj, Window::CommandArguments Arguments)
{
	if (
		Arguments.List.size() == 0
		) {
		Obj->PushBuffer("static void* Commands::RecursiveFolderFileList -> Function terminated, incorrect amount of arguments; expected: 1"); return 0;
	}

	std::string List0 = Arguments.List[0];

	for (
		const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(List0)
		) {
		try {
			if (
				entry.is_regular_file()
				) {
				Obj->PushBuffer(
					entry.path().string()
				);
			}
			else for (
				const std::filesystem::directory_entry& RecursiveEntry : std::filesystem::recursive_directory_iterator(entry.path())
				) {

				Obj->PushBuffer(
					RecursiveEntry.path().string()
				);
			}
		}
		catch (
			const std::exception& ex
			) {
			Obj->PushBuffer(ex.what());
		}

		Obj->PushBuffer("Finished");
	}
}

void* Commands::Start(Window*& Obj, Window::CommandArguments Arguments)
{
	if (
		Arguments.List.size() != 2
		) {
		Obj->PushBuffer("static void* Commands::Start -> Function terminated, incorrect amount of arguments; Expected 2[int, std::filesystem::path -> regularfile]."); return 0;
	}

	int DelaySeconds;

	try {
		DelaySeconds = std::stoi(Arguments.List[0]);
	}
	catch (
		const std::exception& ex
		) {
		Obj->PushBuffer("static void* Commands::Start -> Function terminated, catched error when trying to assign args[0][int]."); return 0;
	}

	std::filesystem::path FilePath = Arguments.List[1];

	Obj->PushBuffer("Application will be run after delay is over...");
	std::this_thread::sleep_for(std::chrono::seconds(DelaySeconds));

	int SystemResponse = system(std::string("start " + FilePath.string()).c_str());

	if (
		SystemResponse == 0
		) {
		Obj->PushBuffer("Application ran successfully."); return 0;
	}

	Obj->PushBuffer("static void* Commands::Start -> System32 error thrown. Application terminated.");
}

Commands::Commands(Window*& obj) : WindowObject(obj)
{
	obj->PushCommand(Commands::Echo, "Echo");
	obj->PushCommand(Commands::Clear, "Clear");
	obj->PushCommand(Commands::RecursiveFolderFileList, "RecursiveFolderFileList");
	obj->PushCommand(Commands::Start, "Start");
};