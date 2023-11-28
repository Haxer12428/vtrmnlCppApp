#pragma once
#include <fstream>
#include <filesystem>
#include <string>
#include <any>

class Config
{
public:
	Config(
		const std::filesystem::path& Path
	);

	void NewConfigVariable(
		const std::string& name, const std::any& value
	);

	struct ConfigVariable
	{
	public:
		ConfigVariable(
			const std::string& name, const std::any& value
		) : name(name), value(value) {

		}
			 
		const std::string name; 
		const std::any value; 
	};

	void HandleConfigFile();

	template<typename T> T GetVariable(
		std::string name
	) {
		std::fstream ConfigFile; ConfigFile.open(
			this->configFilePath, std::ios::in
		);

		T VariableValue = T(); std::string Cl;

		do {
			std::string ClShort = Cl;
			ClShort.resize(name.length());
			if (
				ClShort == name
				)
			{
				std::string FoundValue = Cl.substr(name.length() + 1);

				VariableValue = std::stoi(FoundValue);
			}
		} while (std::getline(ConfigFile, Cl));

		ConfigFile.close();

		return VariableValue;
	}

private:
	std::vector<
		ConfigVariable> ConfigBuffer;
		

	const std::filesystem::path configFilePath;
};
