#include "daybase.hpp"
#include "stringFunctions.h"

#include <string>


typedef std::string primary;

primary parse(
		std::string line)
{
	return line;
}

template <class T>
int getFirstDigit(
		T it,
		T end)
{
	while (it != end)
	{
		if (std::isdigit(*it))
		{
			return (*it) - '0';
		}

		it++;
	}

	return 0;
}

std::string replaceStringRepresentationsOfDigits(
		std::string source)
{
	std::vector<std::pair<std::string, std::string>> replacements = 
	{
		{ "one", "o1e" },
		{ "two", "t2o" },
		{ "three", "t3e" },
		{ "four", "f4r" },
		{ "five", "f5e" },
		{ "six", "s6x" },
		{ "seven", "s7n" },
		{ "eight", "e8t" },
		{ "nine", "n9e" }
	};

	for (auto [target, replacement] : replacements)
	{
		source = aocUtility::string::replace(source, target, replacement);
	}

	return source;
}

int getValueFromLine(
		std::string line,
		bool useStringRepresentations)
{
	if (useStringRepresentations)
	{
		line = replaceStringRepresentationsOfDigits(line);
	}

	auto first = getFirstDigit(line.begin(), line.end());
	auto last = getFirstDigit(line.rbegin(), line.rend());

	return first * 10 + last;
}

std::string partOne(
		std::vector<primary> source)
{
	int result = 0;
	
	for (auto line : source)
	{
		result += getValueFromLine(line, false);
	}

	return std::to_string(result);	
}

std::string partTwo(
		std::vector<primary> source)
{
	int result = 0;
	
	for (auto line : source)
	{
		result += getValueFromLine(line, true);
	}

	return std::to_string(result);	
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/01_input";

	auto parser = aocUtility::createParserForLine<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
