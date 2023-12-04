#include "daybase.hpp"

#include "stringFunctions.h"

#include <algorithm>
#include <cmath>
#include <string>


typedef std::pair<std::vector<int>, std::vector<int>> primary;

primary parse(
		std::string line)
{
	auto splitLine = aocUtility::string::splitByDelimiter(line, ": ");

	auto cardSource = aocUtility::string::replace(splitLine[1], "  ", " ");

	cardSource = aocUtility::string::trim(cardSource);

	auto splitSource = aocUtility::string::splitByDelimiter(cardSource, " | ");

	auto winningNumberSource = aocUtility::string::splitByDelimiter(splitSource[0], " ");
	auto myNumberSource = aocUtility::string::splitByDelimiter(splitSource[1], " ");

	std::vector<int> winningNumbers;

	for (auto n : winningNumberSource)
	{
		winningNumbers.push_back(std::stoi(n));
	}

	std::vector<int> myNumbers;

	for (auto n : myNumberSource)
	{
		myNumbers.push_back(std::stoi(n));
	}

	return std::make_pair(winningNumbers, myNumbers);
}

std::size_t getMatchingCount(
		std::vector<int> winningNumbers,
		std::vector<int> myNumbers)
{
		std::vector<int> numbersUnion;

		for (auto e : winningNumbers)
		{
			if (std::find(myNumbers.begin(), myNumbers.end(), e) != myNumbers.end())
			{
				numbersUnion.push_back(e);
			}
		}

		return numbersUnion.size();
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
			result += (int) pow(2, size - 1);
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
