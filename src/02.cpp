#include "daybase.hpp"

#include <algorithm>
#include <string>
#include <utility>

#include "stringFunctions.h"


typedef std::vector<std::vector<std::pair<std::string, std::size_t>>> primary;

primary parse(
		std::string line)
{
	primary result;

	auto initialSplit = aocUtility::string::splitByDelimiter(line, ": ");

	auto gameSource = initialSplit[1];

	auto splitGameSource = aocUtility::string::splitByDelimiter(gameSource, "; ");

	for (auto cubeSetSource : splitGameSource)
	{
		std::vector<std::pair<std::string, std::size_t>> cubeSet;

		auto splitCubeSetSource = aocUtility::string::splitByDelimiter(cubeSetSource, ", ");

		for (auto cubeSource : splitCubeSetSource)
		{
			auto splitCubeSource = aocUtility::string::splitByDelimiter(cubeSource, " ");

			auto color = splitCubeSource[1];
			auto count = (std::size_t) (std::stoul(splitCubeSource[0]));

			cubeSet.push_back(std::make_pair(color, count));
		}

		result.push_back(cubeSet);
	}

	return result;
}

std::string partOne(
		std::vector<primary> source)
{
	std::size_t id = 1;
	std::size_t totalValid = 0;

	std::size_t redLimit = 12;
	std::size_t greenLimit = 13;
	std::size_t blueLimit = 14;

	for (auto game : source)
	{
		bool validGame = true;

		for (auto set : game)
		{
			for (auto [ color, count ] : set)
			{
				if (color == "red")
					validGame &= count <= redLimit;
				if (color == "green")
					validGame &= count <= greenLimit;
				if (color == "blue")
					validGame &= count <= blueLimit;
			}
		}

		if (validGame)
		{
			totalValid += id;
		}

		id++;
	}

	return std::to_string(totalValid);
}

std::string partTwo(
		std::vector<primary> source)
{
	std::size_t sumOfPower = 0;

	for (auto game : source)
	{
		std::size_t minRed = 0;
		std::size_t minGreen = 0;
		std::size_t minBlue = 0;

		for (auto set : game)
		{
			for (auto [ color, count ] : set)
			{
				if (color == "red")
					minRed = std::max(minRed, count);
				if (color == "green")
					minGreen = std::max(minGreen, count);
				if (color == "blue")
					minBlue = std::max(minBlue, count);
			}
		}

		sumOfPower += (minRed * minGreen * minBlue);
	}

	return std::to_string(sumOfPower);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_02_input";

	auto parser = aocUtility::createParserForLine<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
