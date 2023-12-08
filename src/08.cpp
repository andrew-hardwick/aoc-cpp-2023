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

std::string partOne(
		primary source)
{
	auto [ instructions, graph ] = source;

	std::size_t i = 1;
	std::string currentNode = "AAA";

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

			if (currentNode == "ZZZ")
			{
				return std::to_string(i);
			}

			i++;
		}
	}
}

std::string partTwo(
		primary source)
{
	auto [ instructions, graph ] = source;

	std::size_t i = 1;

	std::vector<std::string> currentNodes;

	for (auto [ node, _ ] : graph)
	{
		if (node[2] == 'A')
		{
			currentNodes.push_back(node);
		}
	}

	while(true)
	{
		for (auto c : instructions)
		{
			bool allOnZ = true;

			for (std::size_t i = 0 ; i < currentNodes.size(); i++)
			{
				auto currentNode = currentNodes.at(i);

				std::cout << i << " " << currentNode << "\n";
				auto [ left, right ] = graph.at(currentNode);

				if (c == 'L')
				{
					currentNode = left;
				}
				else
				{
					currentNode = right;
				}

				currentNodes.at(i) = currentNode;

				allOnZ &= currentNode[2] == 'Z';
			}

			if (allOnZ)
			{
				return std::to_string(i);
			}

			i++;
		}
	}
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_08_test2";

	auto parser = aocUtility::createWholesaleParserForFile<primary>(parse);

	aocUtility::executeWholesale<primary>(filename, parser, partOne, partTwo);

	return 0;
}
