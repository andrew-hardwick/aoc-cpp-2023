#include "daybase.hpp"

#include "stringFunctions.h"

#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>

/***
 * All inputs appear to be six independent looped graphs
 * Each start has only one available end
 * Each start and end pair are the same distance from the
 *   unifying node in their respective loops
 ***/

typedef std::pair<std::string, std::map<std::string, std::pair<std::string, std::string>>> primary;

primary parse(
		const std::vector<std::string>& file)
{
	auto instructions = file[0];

	std::map<std::string, std::pair<std::string, std::string>> graph;
	for (auto it = file.cbegin() + 2; it != file.cend(); it++)
	{
		auto lineSplit = aocUtility::string::splitByDelimiter(*it, " = ");

		auto node = lineSplit[0];

		auto next = aocUtility::string::splitByDelimiter(lineSplit[1].substr(1, 8), ", ");

		graph.emplace(std::make_pair(node, std::make_pair(next[0], next[1])));
	}

	return std::make_pair(instructions, graph);
}

std::size_t findStepsToEnd(
		std::string start,
		std::string instructions,
		std::map<std::string, std::pair<std::string, std::string>> graph,
		std::vector<std::string> targets)
{
	std::string currentNode = start;
	std::size_t stepCount = 1;

	while(true)
	{
		for (auto c : instructions)
		{
			auto [ left, right ] = graph.at(currentNode);

			if (c == 'L')
			{
				currentNode = left;
			}
			else
			{
				currentNode = right;
			}

			auto it = std::find(targets.cbegin(), targets.cend(), currentNode);
			
			if (it != targets.cend())
			{
				return stepCount;
			}

			stepCount++;
		}
	}

	throw std::domain_error("This exception is unreachable with proper input");
}

std::string partOne(
		primary source)
{
	auto [ instructions, graph ] = source;
	std::string start = "AAA";
	std::vector<std::string> targets { "ZZZ" };

	auto result = findStepsToEnd(start, instructions, graph, targets);

	return std::to_string(result);
}

std::string partTwo(
		primary source)
{
	auto [ instructions, graph ] = source;

	std::vector<std::string> starts;
	std::vector<std::string> targets;

	for (auto [ start, _ ] : graph)
	{
		if (start[2] == 'A')
		{
			starts.push_back(start);
		}
		if (start[2] == 'Z')
		{
			targets.push_back(start);
		}
	}

	// Each start only has one possible end
	std::vector<std::size_t> stepsToEnd;

	for (auto start : starts)
	{
		stepsToEnd.push_back(findStepsToEnd(start, instructions, graph, targets));
	}

	std::size_t result = 1;

	for (auto steps : stepsToEnd)
	{
		result = std::lcm(result, steps);
	}

	return std::to_string(result);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_08_input";

	auto parser = aocUtility::createWholesaleParserForFile<primary>(parse);

	aocUtility::executeWholesale<primary>(filename, parser, partOne, partTwo);

	return 0;
}
