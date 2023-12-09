#include "daybase.hpp"

#include <string>
#include <utility>

#include "stringFunctions.h"


typedef std::pair<std::vector<int>, std::vector<std::vector<int>>> primary;

std::vector<std::vector<int>> getSubsequences(
		std::vector<int> sequence)
{
	std::vector<std::vector<int>> subSequences;

	std::vector<int> currentSequence(sequence.cbegin(), sequence.cend());

	bool isZeroes = false;

	while (!isZeroes)
	{
		std::vector<int> subSequence;

		int previous = currentSequence.at(0);

		isZeroes = previous == 0;

		for (auto it = currentSequence.cbegin() + 1; it != currentSequence.cend(); it++)
		{
			auto current = *it;
			
			isZeroes &= current == 0;

			subSequence.push_back(current - previous);

			previous = current;
		}

		if (!isZeroes)
		{
			subSequences.push_back(subSequence);
		}

		currentSequence = subSequence;
	}

	return subSequences;
}

primary parse(
		std::string line)
{
	std::vector<int> sequence;

	auto splitLine = aocUtility::string::splitByDelimiter(line, " ");

	for (auto e : splitLine)
	{
		sequence.push_back(std::stoi(e));
	}

	return std::make_pair(sequence, getSubsequences(sequence));
}

int findNextForwards(
		primary data)
{
	auto [ sequence, subSequences ] = data;

	for (auto it = subSequences.rbegin(); it != subSequences.rend() - 1; it++)
	{
		auto current = *it;
		auto& next = *(it + 1);

		auto lastValueLowerLevel = *current.rbegin();
		auto lastValueNextLevel = *next.rbegin();

		next.push_back(lastValueLowerLevel + lastValueNextLevel);
	}

	return *(sequence.rbegin()) + *(subSequences.at(0).rbegin());
}

int findNextBackwards(
		primary data)
{
	auto [ sequence, subSequences ] = data;

	for (auto it = subSequences.rbegin(); it != subSequences.rend() - 1; it++)
	{
		auto current = *it;
		auto& next = *(it + 1);

		auto lastValueLowerLevel = *current.begin();
		auto lastValueNextLevel = *next.begin();

		next.insert(next.begin(), lastValueNextLevel - lastValueLowerLevel);
	}

	return *(sequence.begin()) - *(subSequences.at(0).begin());
}

std::string partOne(
		std::vector<primary> source)
{
	int total = 0;

	for (auto entry : source)
	{
		total += findNextForwards(entry);
	}

	return std::to_string(total);
}

std::string partTwo(
		std::vector<primary> source)
{
	int total = 0;

	for (auto entry : source)
	{
		total += findNextBackwards(entry);
	}

	return std::to_string(total);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_09_input";

	auto parser = aocUtility::createParserForLine<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
