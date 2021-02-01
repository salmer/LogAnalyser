#include "pch.h"
#include "LogAnalyserLib/LogAnalyserLib.h"

namespace LogAnalyserLib { namespace Testing {

TEST(CommandLineParserTests, Parser_can_arguments)
{
	constexpr int arraySize{7};
	char *testData[arraySize]{"testLocation\\test", "-d", "test\\logs", "-n", "100", "-t", "10"};

	CommandLineParser parser;
	parser.Parse(arraySize, testData);

	ASSERT_EQ(testData[2], parser.GetLogDirectory());
	ASSERT_EQ(std::stoi(testData[4]), parser.GetNumberOfFilesInDirectory());
	ASSERT_EQ(std::stoi(testData[6]), parser.GetNumberOfThreads());
}

TEST(CommandLineParserTests, Parser_can_return_non_mandatory_arguments)
{
	constexpr int arraySize{5};
	char* testData[arraySize]{"testLocation\\test", "-d", "test\\logs", "-n", "100"};

	CommandLineParser parser;
	parser.Parse(arraySize, testData);

	constexpr auto expectedDefaultNumberOfThreads{1};
	ASSERT_EQ(expectedDefaultNumberOfThreads, parser.GetNumberOfThreads());
}

TEST(CommandLineParserTests, Parser_throws_an_exception_if_arguments_are_not_set)
{
	constexpr int arraySize{1};
	char* testData[arraySize]{"testLocation\\test"};

	CommandLineParser parser;
	ASSERT_THROW(parser.Parse(arraySize, testData), std::runtime_error);
}

TEST(CommandLineParserTests, Parser_throws_an_exception_if_cmd_argument_is_unknown)
{
	constexpr int arraySize{3};
	char* testData[arraySize]{"testLocation\\test", "-k", "test\\logs"};

	CommandLineParser parser;
	ASSERT_THROW(parser.Parse(arraySize, testData), std::out_of_range);
}

TEST(CommandLineParserTests, Parser_throws_an_exception_if_mandatory_arguments_are_not_set)
{
	constexpr int arraySize{3};
	char* testData[arraySize]{"testLocation\\test", "-t", "10"};

	CommandLineParser parser;
	ASSERT_THROW(parser.Parse(arraySize, testData), std::runtime_error);
}

TEST(CommandLineParserTests, Parser_throws_an_exception_if_cmd_arguments_are_set_incorrectly)
{
	constexpr int arraySize{2};
	char* testData[arraySize]{"testLocation\\test", "-k"};

	CommandLineParser parser;
	ASSERT_THROW(parser.Parse(arraySize, testData), std::runtime_error);
}

TEST(CommandLineParserTests, Parser_throws_an_exception_if_number_of_files_is_negative)
{
	constexpr int arraySize{7};
	char* testData[arraySize]{"testLocation\\test", "-d", "test\\logs", "-n", "-100", "-t", "10"};

	CommandLineParser parser;
	ASSERT_THROW(parser.Parse(arraySize, testData), std::runtime_error);
}

TEST(CommandLineParserTests, Parser_throws_an_exception_if_number_of_threads_is_negative)
{
	constexpr int arraySize{7};
	char* testData[arraySize]{"testLocation\\test", "-d", "test\\logs", "-n", "100", "-t", "-10"};

	CommandLineParser parser;
	ASSERT_THROW(parser.Parse(arraySize, testData), std::runtime_error);
}

}}