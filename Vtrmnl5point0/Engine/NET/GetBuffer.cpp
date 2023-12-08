#include "../Engine.h"

Engine::NET::GetBuffer::GetBuffer(
	const std::string& URL 
) {
	
}

std::filesystem::path Engine::NET::GetBuffer::ObtainPath() {
	if (
		!std::filesystem::is_directory("C:\\EngineApp0x")
		) {
		std::filesystem::create_directories("C:\\EngineApp0x");
	}

	return "C:\\EngineApp0x\\Download1x.txt";
}

std::vector<std::string> Engine::NET::GetBuffer::Obtain(
	std::filesystem::path Path 
) {
    

    return std::vector<std::string>();
}