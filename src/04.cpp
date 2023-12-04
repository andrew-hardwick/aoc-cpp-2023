#include "daybase.hpp"

#include "stringFunctions.h"

#include <algorithm>
#include <string>


typedef std::pair<std::vector<std::string>, std::vector<std::string>> primary;

primary parse(
		std::string line)
{
	auto splitLine = aocUtility::string::splitByDelimiter(line, ":");

	auto splitSource = aocUtility::string::splitByDelimiter(splitLine[1], " |");

	auto winningNumbers = aocUtility::string::getSubstringsOfLength(splitSource[0], 3);
	auto myNumbers = aocUtility::string::getSubstringsOfLength(splitSource[1], 3);

	return std::make_pair(winningNumbers, myNumbers);
}

template <class T>
std::size_t getMatchingCount(
		std::vector<T> a,
		std::vector<T> b)
{
		std::vector<T> aBUnion;

		for (auto e : a)
		{
			if (std::find(b.begin(), b.end(), e) != b.end())
			{
				aBUnion.push_back(e);
			}
		}

		return aBUnion.size();
}

std::string partOne(
		std::vector<primary> source)
{
	int result = 0;

	for (auto [ winningNumbers, myNumbers ] : source)
	{
		auto size = getMatchingCount(winningNumbers, myNumbers);

		if (size > 0)
		{
			result += 1 << (size - 1);
		}
	}

	return std::to_string(result);
}

std::string partTwo(
		std::vector<primary> source)
{
	std::vector<std::size_t> matchingCounts;
	std::vector<std::size_t> cardCounts;

	for (auto [ winningNumbers, myNumbers ] : source)
	{
		matchingCounts.push_back(getMatchingCount(winningNumbers, myNumbers));
		cardCounts.push_back(1);
	}

	std::size_t totalCardCount = 0;

	for (std::size_t i = 0; i < source.size(); i++)
	{
		std::size_t currentCount = cardCounts.at(i);

		totalCardCount += currentCount;

		for (std::size_t j = 1; j <= matchingCounts.at(i); j++)
		{
			cardCounts.at(j + i) += currentCount;
		}
	}

	return std::to_string(totalCardCount);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_04_input";

	auto parser = aocUtility::createParserForLine<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
