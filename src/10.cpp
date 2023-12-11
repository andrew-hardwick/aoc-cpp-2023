#include "daybase.hpp"

#include <string>
#include <map>
#include <utility>


typedef std::pair<std::size_t, std::map<std::size_t, std::vector<std::size_t>>> primary;

std::size_t Loc(
		std::size_t x,
		std::size_t y,
		std::size_t rowLength)
{
	return x + y * rowLength;
}

std::vector<std::size_t> findNeighborsForStart(
		std::size_t x,
		std::size_t y,
		const std::vector<std::string>& source,
		std::size_t rowLength)
{
	std::vector<std::size_t> result;

	char right = source.at(y).at(x + 1);
	char up = source.at(y - 1).at(x);
	char down = source.at(y + 1).at(x);

	if (x != 0)
	{
		char left = source.at(y).at(x - 1);
		if (left == '-' || left == 'L' || left == 'F')
			result.push_back(Loc(x - 1, y, rowLength));
	}

	if (x < rowLength)
	{
		if (right == '-' || right == 'J' || right == '7')
			result.push_back(Loc(x + 1, y, rowLength));
	}

	if (y != 0)
	{
		if (up == '|' || up == '7' || up == 'F')
			result.push_back(Loc(x, y - 1, rowLength));
	}

	if (y < rowLength)
	{
		if (down == '|' || down == 'L' || down == 'J')
			result.push_back(Loc(x, y + 1, rowLength));
	}

	return result;
}

primary parse(
		const std::vector<std::string>& source)
{
	std::size_t rowLength = source.size(); // source is square;

	std::size_t start = 0;
	std::map<std::size_t, std::vector<std::size_t>> graph;

	std::size_t y = 0;
	for (auto line : source)
	{
		std::size_t x = 0;
		for (auto c : line)
		{
			std::size_t loc = Loc(x, y, rowLength);

			std::vector<std::size_t> neighbors;

			if (c == '|')
			{
				neighbors.push_back(loc - rowLength);
				neighbors.push_back(loc + rowLength);
			}
			else if (c == '-')
			{
				neighbors.push_back(loc - 1);
				neighbors.push_back(loc + 1);
			}
			else if (c == 'L')
			{
				neighbors.push_back(loc - rowLength);
				neighbors.push_back(loc + 1);
			}
			else if (c == 'J')
			{
				neighbors.push_back(loc - rowLength);
				neighbors.push_back(loc - 1);
			}
			else if (c == '7')
			{
				neighbors.push_back(loc - 1);
				neighbors.push_back(loc + rowLength);
			}
			else if (c == 'F')
			{
				neighbors.push_back(loc + 1);
				neighbors.push_back(loc + rowLength);
			}
			else if (c == 'S')
			{
				start = loc;
				neighbors = findNeighborsForStart(x, y, source, rowLength);
			}

			graph.emplace(std::make_pair(loc, neighbors));

			x++;
		}

		y++;
	}

	return std::make_pair(start, graph);
}

std::string partOne(
		primary source)
{
	auto [ start, graph ] = source;

	std::size_t leftPrevPrev = start;
	std::size_t leftPrev = start;
	std::size_t rightPrevPrev = start;
	std::size_t rightPrev = start;

	auto left = graph.at(start)[0];
	auto right = graph.at(start)[1];

	std::size_t length = 1;
	bool overlap = false;
	while (!overlap)
	{
		leftPrevPrev = leftPrev;
		leftPrev = left;

		rightPrevPrev = rightPrev;
		rightPrev = right;

		auto leftSource = graph.at(left);

		if (leftPrevPrev == leftSource.at(0))
			left = leftSource.at(1);
		else
			left = leftSource.at(0);

		auto rightSource = graph.at(right);
		if (rightPrevPrev == rightSource.at(0))
			right = rightSource.at(1);
		else
			right = rightSource.at(0);

		overlap = (left == right) || (left == rightPrev) || (right == leftPrev);

		length++;
	}

	return std::to_string(length);
}

std::string partTwo(
		primary source)
{
	return "nonimpl";
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_10_input";

	auto parser = aocUtility::createWholesaleParserForFile<primary>(parse);

	aocUtility::executeWholesale<primary>(filename, parser, partOne, partTwo);

	return 0;
}
