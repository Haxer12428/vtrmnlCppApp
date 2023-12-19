#pragma once
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

namespace engine {


	class process {
	public:
		process(); 

		const bool find_by_pid(
			const DWORD& pid
		);

		const bool find_by_name(
			const std::string& name
		); 

		const HANDLE get_process() const;

		const bool open_process();
		const bool close_process(); 
		

	private:
		DWORD process_id; 
		HANDLE process_handle; 
	};

	class memory : engine::process
	{
	public:
		memory(
			engine::process process
		); 

		enum format
		{
			B = 1, 
			KB = 1024,
			MB = 1024 * 1024
		};

		const double get_usage(
			engine::memory::format format
		);

	private:
		
	};

	class processor {
	public:

		static const double get_usage() {
			FILETIME idleTime, kernelTime, userTime;

			if (
				!GetSystemTimes(&idleTime, &kernelTime, &userTime)
				) {
				return -1.0;
			}

			static unsigned long long _previousTotalTicks = 0;
			static unsigned long long _previousIdleTicks = 0;

			unsigned long long idle = (
				(unsigned long long)idleTime.dwHighDateTime << 32
				) | idleTime.dwLowDateTime;

			unsigned long long kernel = (
				(unsigned long long)kernelTime.dwHighDateTime << 32
				) | kernelTime.dwLowDateTime;

			unsigned long long user = (
				(unsigned long long)userTime.dwHighDateTime << 32
				) | userTime.dwLowDateTime;

			unsigned long long totalTicks = (
				kernel + user
				);

			unsigned long long totalTicksSinceLastTime = (
				totalTicks - _previousTotalTicks
				);

			unsigned long long idleTicksSinceLastTime = (
				idle - _previousIdleTicks
				);

			double Result = 1.0 - (
				(double)idleTicksSinceLastTime
				) / totalTicksSinceLastTime;

			_previousTotalTicks = totalTicks;
			_previousIdleTicks = idle;

			return Result * 100.0;
		}
	};

	class file {
	public:
		file(
			const std::filesystem::path& file_path
		); 

		const bool write_vector_buffer(
			const std::vector<std::string>& buffer
		) const; 

		const void set_path(
			const std::filesystem::path& file_path
		); 

		const std::filesystem::path get_path() const; 

		const std::vector<std::string> get_buffer_in_vector(); 

	private:
		std::filesystem::path file_path; 
	};

	class string {
	public:
		string(
			const std::string& str
		); 

		const size_t find_phrase(
			const std::string& phrase
		) const; 

		const void set_string(
			const std::string& str
		);

		const std::vector<std::string> get_vector() const; 

		const std::string get_string() const; 

	private:
		std::string str; 
	};

	class config {
	public:
		config(
			const std::filesystem::path& file_path
		);

		std::filesystem::path get_path() const;

		const std::string desire(
			const std::string& name, const std::string& default_value
		) const;

	private:
		const bool file_available() const; 

		const bool make_file() const; 

		const bool make_desire(
			const std::string& name, const std::string& value
		) const; 

		std::filesystem::path file_path; 
	};

	class vector {
	public:
		static const std::string transform_string_vector_to_string(
			const std::vector<std::string>& buffer
		);

		static const std::vector<std::string> find_in_phrases(
			const std::string& str, const std::string& phrases
		);

		static const std::vector<int> transform_string_vector_to_int_vector(
			const std::vector<std::string>& buffer
		);

		template<typename T> size_t find_value(
			const std::vector<T>& buffer, T phrase
		) {
			for (
				size_t iterator = 0; iterator < buffer.size(); iterator++
				) {
				if (
					buffer[iterator] == phrase
					) return iterator;
			}
			return -1;
		}

		const size_t find_phrase(
			const std::vector<std::string>& buffer, std::string phrase
		) {
			for (
				size_t iterator = 0; iterator < buffer.size(); iterator++
				) {
				if (
					engine::string(buffer[iterator]).find_phrase(phrase) != std::string::npos
					) return iterator;
			}
			return -1;
		}
	};
};