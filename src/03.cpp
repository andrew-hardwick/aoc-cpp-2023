#include "daybase.hpp"
#include "point.h"

#include <cctype>
#include <sstream>
#include <string>
#include <tuple>


// x, y, length, value
typedef std::tuple<std::size_t, std::size_t, std::size_t, int, char> primary;

std::vector<primary> parse(
		const std::vector<std::string>& file)
{
	std::vector<primary> result;

	std::size_t y = 0;

	for (auto line : file)
	{
		std::size_t x = 0;

		std::stringstream builder;
		bool parsingNumber = false;

		std::size_t numberStart = 0;

		for (auto c : line)
		{
			auto isDigit = std::isdigit(c);

			if (parsingNumber)
			{
				if (isDigit)
				{
					builder << c;
				}
				else
				{
					std::string numberSource = builder.str();

					result.push_back(std::make_tuple(numberStart, y, numberSource.size(), std::stoi(numberSource), 'i'));

					parsingNumber = false;
				}
			}
			else if (isDigit)
			{
				builder.str("");

				numberStart = x;
				parsingNumber = true;

				builder << c;
			}

			if (!(isDigit || c == '.'))
			{
				result.push_back(std::make_tuple(x, y, 1, -1, c));
			}

			x++;
		}

		if (parsingNumber)
		{
				std::string numberSource = builder.str();

				result.push_back(std::make_tuple(numberStart, y, numberSource.size(), std::stoi(numberSource), 'i'));
		}

		y++;
	}

	return result;
}

bool checkIfAdjacent(
		aocUtility::Point pointNumber,
		std::size_t numberLength,
		aocUtility::Point pointSymbol)
{
	bool result = false;

	for (std::size_t i = 0; i < numberLength; i++)
	{
		auto test = pointNumber.shiftX(i);

		result |= test.isAdjacent(pointSymbol);
	}

	return result;
}

bool checkIfAdjacentToAnything(
		aocUtility::Point point,
		std::size_t length,
		std::vector<aocUtility::Point> itemsToCheckAgainst)
{
	bool result = false;

	for (auto p : itemsToCheckAgainst)
	{
		result |= checkIfAdjacent(point, length, p);
	}

	return result;
}

int getGearRatio(
		aocUtility::Point gearLoc,
		const std::vector<std::tuple<aocUtility::Point, std::size_t, int>> numbers)
{
	std::vector<int> adjacentNumbers;

	for (auto [ point, length, value ] : numbers)
	{
		if (checkIfAdjacent(point, length, gearLoc))
		{
			adjacentNumbers.push_back(value);
		}
	}

	if (adjacentNumbers.size() == 2)
	{
		return adjacentNumbers.at(0) * adjacentNumbers.at(1);
	}

	return 0;
}

std::string partOne(
		std::vector<primary> source)
{
	std::vector<aocUtility::Point> symbolLocations;
	std::vector<std::tuple<aocUtility::Point, std::size_t, int>> numbers;

	for (auto [ x, y, length, value, _ ] : source)
	{
		if (value == -1)
		{
			symbolLocations.push_back(aocUtility::Point(x, y));
			continue;
		}

		numbers.push_back(std::make_tuple(aocUtility::Point(x, y), length, value));
	}

	std::vector<int> matchingNumbers;

	for (auto [ key, length, value ] : numbers)
	{
		if (checkIfAdjacentToAnything(key, length, symbolLocations))
		{
			matchingNumbers.push_back(value);
		}
	}

	int sum = 0;

	for (auto value : matchingNumbers)
	{
		sum += value;
	}

	return std::to_string(sum);
}

std::string partTwo(
		std::vector<primary> source)
{
	std::vector<aocUtility::Point> gearLocations;
	std::vector<std::tuple<aocUtility::Point, std::size_t, int>> numbers;

	for (auto [ x, y, length, value, symbol ] : source)
	{
		if (symbol == '*')
		{
			gearLocations.push_back(aocUtility::Point(x, y));
			continue;
		}

		numbers.push_back(std::make_tuple(aocUtility::Point(x, y), length, value));
	}

	int sum = 0;

	for (auto gearLoc : gearLocations)
	{
		sum += getGearRatio(gearLoc, numbers);
	}

	return std::to_string(sum);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_03_input";
	//auto filename = "input/2023_03_test1";

	auto parser = aocUtility::createParserForFile<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}

