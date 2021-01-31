#pragma once

#include <string>
#include <queue>

#define FMT_HEADER_ONLY
#include "fmt\format.h"

namespace LogAnalyserLib
{

using format_args = fmt::format_args;

class ConsoleAppLogger
{
public:
	template <typename T, typename... Args>
	static void LogMessage(const T& format, Args&&... args)
	{
		Log(format, fmt::make_args_checked<Args...>(format, args...));
	}

private:
	static void Log(fmt::string_view str, format_args args);
};

}