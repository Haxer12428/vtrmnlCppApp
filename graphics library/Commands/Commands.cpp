#include "Commands.h"

std::filesystem::path RoutePath = Sdl::App::GetPath();

void* Commands::Clear(Window*& Obj, Window::CommandArguments)
{
	Obj->ClearTerminalBuffer(); return 0;
}

void* Commands::RecursiveFolderFileList(Window*& Obj, Window::CommandArguments Arguments)
{
	Obj->NewLine();
	if (
		Arguments.List.size() == 0
		) {
		Obj->PushBuffer("static void* Commands::RecursiveFolderFileList -> Function terminated, incorrect amount of arguments; expected: 1"); return 0;
	}

	std::string List0 = Commands::AddRoute(Arguments.List[0]).string();

	for (
		const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(List0)
		) {
		try {
			if (
				entry.is_regular_file()
				) {
				Obj->PushBuffer(
					"`" + entry.path().string()
				);
			}
			else for (
				const std::filesystem::directory_entry& RecursiveEntry : std::filesystem::recursive_directory_iterator(entry.path())
				) {

				Obj->PushBuffer(
					"`" + RecursiveEntry.path().string()
				);
			}
		}
		catch (
			const std::exception& ex
			) {
			Obj->PushBuffer(ex.what());
		}
	}
	Obj->NewLine();
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

	std::filesystem::path FilePath = Commands::AddRoute(Arguments.List[1]);

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

void* Commands::History(Window*& Obj, Window::CommandArguments Arguments)
{
	if (
		Arguments.List.size() == 0
		) {
		
		for (
			const std::string& history : Obj->GetTerminalCommandHistoryBuffer()
			) Obj->PushBuffer(history);
		return 0;
	}

	int HistoryLenght;

	try {
		HistoryLenght = std::stoi(Arguments.List[0]);
	}
	catch (
		const std::exception& ex
		) {
		throw std::exception("static void* Commands::History -> Function terminated, catched error when trying to assing arg[0][int/size_t];");
	}

	for (
		const std::string& history : Obj->GetTerminalCommandHistoryBuffer(HistoryLenght)
		) Obj->PushBuffer(history); 
	return 0;
}

void* Commands::HistoryManualSwitch(Window*& Obj, Window::CommandArguments Arguments)
{
	if (
		Arguments.List.size() != 1
		) throw std::exception("static void* Commands::HistoryManualSwitch -> Function terminated, invaild amount of arguments; Expected 1[int|size_t].");

	int HistoryPosition; 

	try {
		HistoryPosition = std::stoi(Arguments.List[0]);
	}
	catch (
		const std::exception& ex
		) {
		throw std::exception("static void* Commands::HistoryManualSwitch -> Function terminated, catched error when trying to assign arg[0][int/size_t];");
	}

	try {
		Obj->RunHistory(HistoryPosition);
	}
	catch (
		const std::exception& ex
		) {
		throw ex;
	}
		
		
	return 0;
}

void* Commands::Move(Window*& Obj, Window::CommandArguments Arguments)
{
	if (
		Arguments.List.size() != 2
		) throw std::exception("Commands::Move -> Function terminated, incorrect amount of arguments; Expected 2[from: std::filesystem::path, to: std::filesystem::path].");

	if (
		!std::filesystem::is_regular_file(Commands::AddRoute(Arguments.List[0]))
		) throw std::exception("Commands::Move -> Function terminated, FROM_FILE doesn't exist.");

	std::filesystem::copy_file(
		Commands::AddRoute(Arguments.List[0]), Commands::AddRoute(Arguments.List[1])
	);

	std::filesystem::remove(
		Commands::AddRoute(Arguments.List[0])
	);
}

void* Commands::NetOpenBrowserURL(Window*& Obj, Window::CommandArguments Arguments)
{
	if (
		Arguments.List.size() == 0
		) throw std::exception("Commands::NetOpenBrowserURL -> Function terminated, incorrect amount of arguments; Expected 1[std::string].");

	std::string URL = Arguments.List[0];

	std::system(("xdg-open " + std::string(URL)).c_str());
}

void* Commands::Help(Window*& Obj, Window::CommandArguments)
{
	for (
		Window::CommandFunc CommandStruct : Obj->GetTerminalAssignedCommands()
		) {
		Obj->NewLine(); Obj->PushBufferInVector(CommandStruct.AssignedHelp);
	}
}

void* Commands::Route(Window*& Obj, Window::CommandArguments Arguments)
{
	if (
		Arguments.List.size() == 0
		) {
		Obj->PushBuffer(RoutePath.string()); return 0;
	}

	std::string NewRoute = Commands::AddRoute(Arguments.List[0]).string();

	if (
		!std::filesystem::is_directory(NewRoute)
		) throw std::exception("Commands::Route -> Given route, arg[0] must be a valid directory.");

	Obj->PushBuffer(RoutePath.string() + " -> " + NewRoute);

	RoutePath = NewRoute;
}

const std::filesystem::path Commands::AddRoute(
	const std::filesystem::path& path
) {
	std::string Shortified = path.string();
	Shortified.resize(6);

	if (
		Shortified == "_ROUTE"
		) {
		return RoutePath.string() + path.string().substr(6);
	}

	return path;
};

void* Commands::fCopy(Window*& Obj, Window::CommandArguments Arguments)
{
	std::filesystem::path _FROM = Commands::AddRoute(Arguments.List[0]);
	std::filesystem::path _TO = Commands::AddRoute(Arguments.List[1]);

	if (
		!std::filesystem::is_regular_file(_FROM)
		) throw std::exception("static void* Commands::fCopy -> Function terminated, _FROM file ain't a existing.");

	bool Response = std::filesystem::copy_file(_FROM, _TO);

	if (
		!Response
		) throw std::exception("static void* Commands::fCopy -> Function terminated, unknown error occured");

	return 0; 
}

void* Commands::List(Window*& Obj, Window::CommandArguments Arguments)
{
	std::filesystem::path _FROM = Commands::AddRoute(Arguments.List[0]);

	if (
		!std::filesystem::is_directory(_FROM)
		) throw std::exception("static void* Commands::List -> Function termianted, directory is invaild");
	Obj->NewLine();

	for (
		const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(_FROM)
		) {
		Obj->PushBuffer(
			"`" + entry.path().string()
		);
	} Obj->NewLine();

	return 0;
}

void* Commands::MemoryTotal(
	Window*& Obj, Window::CommandArguments Arguments
) {
	Obj->PushBuffer(std::to_string(Sdl::Memory().GetTotalMemory(Sdl::Memory::MB)) + " MB");
}

int MonitorStatusFunction()
{
	return static_cast<int>(Sdl::Memory().GetMemoryUsage(Sdl::Memory::KB));
}

void* Commands::MemoryMonitorUsage(
	Window*& Obj, Window::CommandArguments Arguments
) {
	Graph* Monitor = new Graph("Memory Usage Monitor", static_cast<int>(Sdl::Memory().GetTotalMemory(Sdl::Memory::KB)));
	Monitor->AssignStatusFunction(MonitorStatusFunction);

	return 0; 
}

int CPUMonitorStatusFunction()
{
	return static_cast<int>(Sdl::CPU().GetUsage());
}

void* Commands::CPUMonitorUsage(
	Window*& Obj, Window::CommandArguments Arguments
) {
	Graph* Monitor = new Graph("CPU Usage Monitor", 100);
	Monitor->AssignStatusFunction(CPUMonitorStatusFunction);

	return 0;
}

int MemoryMonitorSelfLoadFunction()
{
	return static_cast<int>(Sdl::Memory().GetMemoryUsageForCurrentProcess(Sdl::Memory::KB));
}

void* Commands::MemoryMonitorUsageSelf(
	Window*& Obj, Window::CommandArguments Arguments
) {
	Graph* Monitor = new Graph("Memory Self Usage Monitor", -1);
	Monitor->AssignStatusFunction(MemoryMonitorSelfLoadFunction);

	return 0;
}

int CPUMonitorFreqStatusFunction()
{
	return static_cast<int>(Sdl::CPU().GetFrequency());
}

void* Commands::CPUMonitorFrequency(
	Window*& Obj, Window::CommandArguments Arguments
) {
	Graph* Monitor = new Graph("CPU Frequency Monitor", -1);
	Monitor->AssignStatusFunction(CPUMonitorFreqStatusFunction);

	return 0;
}


Commands::Commands(Window*& obj) : WindowObject(obj)
{

	obj->PushCommand(Commands::MemoryMonitorUsage, "Memory.Monitor->Usage", std::vector<std::string>{"`Memory.Monitor->Usage", "  *Function used to monitor MEMORY usage by the system."});

	obj->PushCommand(Commands::MemoryMonitorUsageSelf, "Memory.Monitor->Usage.Self", std::vector<std::string>{"`Memory.Monitor->Usage.Self", "  *Function used to monitor memory use of the program."});

	obj->PushCommand(Commands::CPUMonitorFrequency, "CPU.Monitor->Frequency", std::vector<std::string>{"`CPU.Monitor->Frequency", "  *Function used to monitor CPU frequency."});

	obj->PushCommand(Commands::CPUMonitorUsage, "CPU.Monitor->Usage", std::vector<std::string>{"`CPU.Monitor->Usage", "  *Function used to monitor CPU usage by the system."});

	obj->PushCommand(Commands::MemoryTotal, "Memory.Total", std::vector<std::string>{"`Memory.Total", "  *Function used to display total memory size in MB format."});

	obj->PushCommand(Commands::fCopy, "fCopy", std::vector<std::string>{"`fCopy", "  *Command used to copy file", "  *Must be used with arguments: [from: std::filesystem::path, to: std::filesystem::path]"});

	obj->PushCommand(Commands::Route, "Route", std::vector<std::string>{"`Route", "  *Command used to help with file paths", "  *Can be used with arguments: [print: none | set: std::filesystem::path]"});

	obj->PushCommand(Commands::Move, "Move", std::vector<std::string>{"`Move", "  *Command used to move files.", "  *Must be used with arguments: [from: std::filesystem::path, to: std::filesystem::path]"});

	obj->PushCommand(Commands::Help, "Help", std::vector<std::string>{"`Help", "  *Command used to list every possible command with description."});

	obj->PushCommand(Commands::Echo, "Echo", std::vector<std::string>{
		"`Echo",
		"  *Function used to display: [usermsg, file]",
		"  *Can be used with arguments: [usersmg: std::string, file: _FILE:std::filesystem::path]",
		"  *When '_FILE:' is added function mode is switched to display file"
	});


	obj->PushCommand(Commands::Clear, "Clear", std::vector<std::string>{
		"`Clear",
		"  *Function used to clear terminal buffer"
	});


	obj->PushCommand(Commands::RecursiveFolderFileList, "RecursiveFolderFileList", std::vector<std::string>{
		"`RecursiveFolderFileList",
		"  *Function used to display every file found in given folder",
		"  *Must be used with arguments: [startingFolderPath: std::filesystem::path]",
		"  *When access is restricted may skip file or throw errors"
	});


	obj->PushCommand(Commands::Start, "Start", std::vector<std::string>{
		"`Start",
		"  *Function used to execute file",
		"  *Must be used with arguments: [delaySeconds: int, execpath: std::filesystem::path",
		"  *Function will execute a file after the delay is over"
	});


	obj->PushCommand(Commands::History, "History", std::vector<std::string>{
		"`History",
		"  *Function used to display terminal command history buffer",
		"  *Can be used with arguments: [displayLenght: int]"
	});


	obj->PushCommand(Commands::HistoryManualSwitch, "!", std::vector<std::string>{
		"`! | HistoryManualSwitch",
		"  *Command used to execute command from terminal history buffer",
		"  *Must be used with arguments: [historyPosition: int|size_t]", 
		"  *Cannot execute `!` command to avoid memory leaks",
		"  *May throw errors when position is invaild"
	});

	obj->PushCommand(Commands::NetOpenBrowserURL, "NET.Open.BrowserURL", std::vector<std::string>{
		"`NET.Open.BrowserURL",
		"  *Command used to open URL",
		"  *Must be used with arguments: [URL: std::string]",
		"  *Requires internet connection to properly load URL"
	});
};