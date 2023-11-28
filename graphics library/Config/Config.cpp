#include "Config.h"

Config::Config(
	const std::filesystem::path& path
) : configFilePath(path)
{
	
}

void Config::NewConfigVariable(
	const std::string& name, const std::any& value
) {
	this->ConfigBuffer.push_back(
		Config::ConfigVariable(name, value)
	);
}

void Config::HandleConfigFile()
{
	if (
		std::filesystem::exists(this->configFilePath)
		) return;

	std::string WritableBuffer; 

	std::fstream ConfigFile; ConfigFile.open(
		this->configFilePath, std::ios::out
	);

	for (
		Config::ConfigVariable& Var : this->ConfigBuffer
		)
	{
		WritableBuffer += (
			Var.name + "=" + std::any_cast<std::string>(Var.value) + "\n"
			);
	}

	ConfigFile << WritableBuffer; ConfigFile.close();
}