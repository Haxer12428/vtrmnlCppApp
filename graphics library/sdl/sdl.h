#pragma once
#include <filesystem>
#include <string>

namespace Sdl
{
	class App
	{
	public:
		static const std::filesystem::path GetPath();
	};
}