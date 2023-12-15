#include "daybase.hpp"

#include "point.h"

#include <string>
#include <tuple>


typedef std::tuple<aocUtility::Point, std::size_t, std::size_t> primary;

std::vector<primary> parse(
		const std::vector<std::string>& file)
{
	std::vector<primary> result;

	// file is must contain at least one record and be rectangular
	std::size_t width = file.at(0).size();

	std::vector<std::size_t> emptyColumns;

	std::size_t emptyColumn = 0;

	// cache blank columns
	for (std::size_t x = 0; x < file.size(); x++)
	{
		bool isEmpty = true;
		for (std::size_t y = 0; y < width; y++)
		{
			isEmpty &= file.at(y).at(x) == '.';
		}

		if (isEmpty)
		{
			emptyColumn++;
		}

		emptyColumns.push_back(emptyColumn);
	}

	std::size_t emptyRow = 0;

	for (std::size_t y = 0; y < file.size(); y++)
	{
		auto line = file.at(y);

		bool isEmpty = true;

		for (std::size_t x = 0; x < line.size(); x++)
		{
			if (line.at(x) == '#')
			{
				isEmpty = false;

				result.push_back(std::make_tuple(aocUtility::Point(x, y), emptyColumns.at(x), emptyRow));
			}
		}

		if (isEmpty)
		{
			emptyRow++;
		}
	}

	return result;
}

std::string calculateTotalDistance(
		const std::vector<primary>& source,
		std::size_t expansionFactor)
{
	std::size_t totalDistance = 0;

	expansionFactor--;

	for (std::size_t i = 0; i < source.size(); i++)
	{
		auto [ p1, p1ExtraX, p1ExtraY ] = source.at(i);

		auto p1x = p1.x + (p1ExtraX * expansionFactor);
		auto p1y = p1.y + (p1ExtraY * expansionFactor);
		
		for (std::size_t j = i + 1; j < source.size(); j++)
		{
			auto [ p2, p2ExtraX, p2ExtraY ] = source.at(j);

			auto p2x = p2.x + (p2ExtraX * expansionFactor);
			auto p2y = p2.y + (p2ExtraY * expansionFactor);

			auto deltaX = std::max(p1x, p2x) - std::min(p1x, p2x);
			auto deltaY = std::max(p1y, p2y) - std::min(p1y, p2y);

			auto distance = deltaX + deltaY;

			totalDistance += distance;
		}
	}

	return std::to_string(totalDistance);
}

std::string partOne(
		std::vector<primary> source)
{
	return calculateTotalDistance(source, 2);
}

std::string partTwo(
		std::vector<primary> source)
{
	return calculateTotalDistance(source, 1000000);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_11_input";

	auto parser = aocUtility::createParserForFile<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
