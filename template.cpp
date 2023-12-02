#include "daybase.hpp"

#include <string>


typedef int primary;

primary parse(
		char c)
//		std::string line)
{
	return 0;
}

std::string partOne(
		std::vector<primary> source)
{
	return "nonimpl";
}

std::string partTwo(
		std::vector<primary> source)
{
	return "nonimpl";
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/_input";

	auto parser = aocUtility::createParserForChar<primary>(parse);
//	auto parser = aocUtility::createParserForLine<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
