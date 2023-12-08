#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <Psapi.h>
#include <TlHelp32.h>
#include <codecvt>
#include <fstream>

namespace Engine
{
	class Debug
	{
	public:
		enum TYPES
		{
			FAIL = 0,
			WARNING = 1, 
			MESSAGE = 2
		};

		struct Object
		{
		public:
			Object(
				const std::string& Message, Engine::Debug::TYPES Type
			) : Message(Message), Type(Type) {

			}

			const std::string& What() {
				return this->Message;
			}

			const Engine::Debug::TYPES GetType() {
				return this->Type;
			}

		private:
			const std::string Message; const Engine::Debug::TYPES Type; 
		};
	};

	class String
	{
	public:

		static const size_t Find(
			const std::string& _STR, const std::string& _FIND
		); 

		static const std::vector<std::string> GetVector(
			const std::string& _STR
		);
	};

	class Process
	{
	public:
		Process();

		void FindPID(
			const DWORD& PID
		);

		void FindName(
			const std::string& Name
		);

		HANDLE GetProcessHandle();

	private:

		HANDLE PROCESS_HANDLE;
		DWORD PID; 
	};

	class Vector
	{
	public:
		static const std::vector<int> TransformStringToInt(
			std::vector<std::string> _VECTOR
		) {
			std::vector<int> _TRANSFORMED; 

			for (
				std::string _STR : _VECTOR
				) _TRANSFORMED.push_back(std::stoi(_STR));

			return _TRANSFORMED;
		}

		template<typename T> static const size_t Find(
			std::vector<T> _VECTOR, T _PARAM
		) {
			const size_t _AT = -1; 

			for (
				size_t Iterator = 0; Iterator < _VECTOR.size(); Iterator++ 
				) {
				if (
					_VECTOR[Iterator] == _PARAM
					) return Iterator;
			}

			return _AT; 
		}
	};

	class Memory
	{
	public:
		enum FORMAT
		{
			B = 1,
			KB = 1024,
			MB = (1024 * 1024),
			GB = (1024 * 1024 * 1024)
		};

		Memory();

		const double GetAllocated(
			Engine::Memory::FORMAT _Format
		);

		const double GetUsed(
			Engine::Memory::FORMAT _Format
		);

		const double GetFree(
			Engine::Memory::FORMAT _Format
		);

		std::string GetProcessWithHighestMemoryConsumption(
			std::vector<std::string> _SKIP = std::vector<std::string>{}
		);

		class ofProcess : public Engine::Process
		{
		public:
			ofProcess(
				Engine::Process Process
			); 

			const double Usage(
				Engine::Memory::FORMAT _Format
			);

		private:

		};

	private:
		void Update(); 

		MEMORYSTATUSEX MemoryStatus;
	};

	namespace CPU
	{
		const double GetUsage();
	};


	namespace NET
	{
		class GetBuffer
		{
		public:
			GetBuffer(
				const std::string& URL
			);

		private:
			std::vector<std::string> Obtain(
				std::filesystem::path Path
			);

			std::filesystem::path ObtainPath();

			const std::string URL;
		};
	};

	class Config
	{
	public:
		Config(
			const std::filesystem::path& _PATH
		);

		const std::string Desire(
			const std::string& _NAME, const std::string& _DEFAULTvalue
		);

		std::filesystem::path GetPath() const {
			return this->_PATH;
		}

	private:
		void HandleFile();

		std::filesystem::path _PATH; 
	};
}