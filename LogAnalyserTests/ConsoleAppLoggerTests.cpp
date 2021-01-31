#include "pch.h"
#include "LogAnalyserLib/LogAnalyserLib.h"

namespace LogAnalyserLib { namespace Testing {

TEST(ConsoleAppLoggerTests, Logger_can_log_message)
{
	ASSERT_NO_THROW(ConsoleAppLogger::LogMessage("Test message"));
	ASSERT_NO_THROW(ConsoleAppLogger::LogMessage("Test message: {}, {}, {}", 10, "test" , ""));
	ASSERT_NO_THROW(ConsoleAppLogger::LogMessage("Test message: {}, {}, {}", 10.5, .3f, ""));
	ASSERT_NO_THROW(ConsoleAppLogger::LogMessage("Test message: {}, {}", 10, "test", ""));
}

TEST(ConsoleAppLoggerTests, Logger_throws_an_exception_if_message_formatted_incorrectly)
{
	ASSERT_ANY_THROW(ConsoleAppLogger::LogMessage("Test message: {}, {}, {}", 10.5, .3f));
}

}}