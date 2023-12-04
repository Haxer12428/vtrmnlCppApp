#pragma once
#include <filesystem>
#include <string>
#include <windows.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <pdh.h>
#include <Psapi.h>

#pragma comment(lib, "pdh.lib")


namespace Sdl
{
	class App
	{
	public:
		static const std::filesystem::path GetPath();
	};

	class Memory
	{
	public:
		Memory();

		enum Format
		{
			KB = 1024,
			MB = 1024 * 1024,
			GB = 1024 * 1024 * 1024,
			TB = 1024 * 1024 * 1024 * 1024
		};

		const double GetTotalMemory(
			Sdl::Memory::Format Format
		);

		const double GetMemoryUsage(
			Sdl::Memory::Format Format
		);

		const double GetMemoryUsageForCurrentProcess(
			Sdl::Memory::Format Format
		); 

	private:
		MEMORYSTATUSEX MemoryInfo; 
	};

	class CPU
	{
	public:
		CPU(); 

		const double GetUsage();

		const double GetFrequency();
	};
}