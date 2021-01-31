#include "pch.h"
#include "ConsoleAppLogger.h"
#include <fmt/chrono.h>

namespace LogAnalyserLib {

void ConsoleAppLogger::Log(fmt::string_view str, format_args args)
{
	const auto time{fmt::format("{:%Y-%m-%d, %H:%M:%S}: ", fmt::localtime(std::time(nullptr)))};
	const auto msg{fmt::vformat(str, args)};
	fmt::print("{} : {}\n", time, msg);
}

}