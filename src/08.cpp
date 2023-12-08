#include "daybase.hpp"

#include "stringFunctions.h"

#include <map>
#include <string>
#include <utility>


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

std::map<std::string, std::size_t> findStepsToEach(
		std::string start,
		std::string instructions,
		std::map<std::string, std::pair<std::string, std::string>> graph,
		std::vector<std::string> targets)
{
	std::size_t targetLength = targets.size();

	std::map<std::string, std::size_t> result;

	std::string currentNode = start;
	std::size_t stepCount = 1;

	std::vector<std::pair<std::size_t, std::string>> states;

	while (result.size() != targetLength)
	{
		std::size_t instructionIndex = 0;

		for (auto c : instructions)
		{
			auto state = std::make_pair(instructionIndex, currentNode);

			if (std::find(states.cbegin(), states.cend(), state) != states.cend())
			{
				return result;
			}

			states.push_back(state);

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
				result.emplace(std::make_pair(*it, stepCount));
				
				targets.erase(it);
			}

			if (currentNode == start)
			{
				return result;
			}

			instructionIndex++;
			stepCount++;
		}
	}

	return result;
}

std::string partOne(
		primary source)
{
	auto [ instructions, graph ] = source;
	std::string start = "AAA";
	std::vector<std::string> targets { "ZZZ" };

	auto result = findStepsToEach(start, instructions, graph, targets);

	return std::to_string(result.at("ZZZ"));
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

	std::vector<std::map<std::string, std::size_t>> stepsToEachFromEach;

	for (auto start : starts)
	{
		stepsToEachFromEach.push_back(findStepsToEach(start, instructions, graph, targets));
	}

	for (std::size_t i = 0; i < starts.size(); i++)
	{
	}

	return "nonimpl";
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
