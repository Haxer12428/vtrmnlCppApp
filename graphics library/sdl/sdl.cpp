#include "sdl.h"

const std::filesystem::path Sdl::App::GetPath()
{
    //not working nice windows.h API
	return std::filesystem::path("C:\\");
}