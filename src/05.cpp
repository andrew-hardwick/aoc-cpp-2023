#include "daybase.hpp"

#include "stringFunctions.h"

#include <limits>
#include <string>
#include <vector>


typedef std::pair<std::vector<std::size_t>, std::vector<std::vector<std::vector<std::size_t>>>> primary;

primary parse(
		const std::vector<std::string>& file)
{
	auto seedSource = aocUtility::string::splitByDelimiter(file.at(0), ": ");
	seedSource = aocUtility::string::splitByDelimiter(seedSource[1], " ");

	std::vector<std::size_t> seeds;
	for (auto e : seedSource)
	{
		seeds.push_back(std::stoul(e));
	}

	std::vector<std::string> map_source(file.begin() + 2, file.end());

	std::vector<std::vector<std::size_t>> workingMap;
	std::vector<std::vector<std::vector<std::size_t>>> maps;

	for (auto line : map_source)
	{
		if (line.find("map") != std::string::npos)
		{
			workingMap = std::vector<std::vector<std::size_t>>();
		}
		else if (line.size() == 0)
		{
			maps.push_back(workingMap);
		}
		else
		{
			std::vector<std::size_t> mapEntry;
			auto mapEntrySource = aocUtility::string::splitByDelimiter(line, " ");

			for (auto e : mapEntrySource)
			{
				mapEntry.push_back(std::stoul(e));
			}

			workingMap.push_back(mapEntry);
		}
	}

	maps.push_back(workingMap);

	return std::make_pair(seeds, maps);
}

std::vector<std::pair<std::size_t, std::size_t>> applyMap(
		std::vector<std::pair<std::size_t, std::size_t>> source,
		const std::vector<std::vector<std::size_t>>& fullMap)
{
	std::vector<std::pair<std::size_t, std::size_t>> result;

	std::vector<bool> handled;

	for (std::size_t i = 0; i < source.size(); i++)
	{
		handled.push_back(false);
	}

	for (const auto& mapToApply : fullMap)
	{
		auto mapDest = mapToApply.at(0);
		auto mapSour = mapToApply.at(1);
		auto mapLeng = mapToApply.at(2);
		auto mapEnd = mapSour + mapLeng - 1;

		for (std::size_t i = 0; i < source.size(); i++)
		{
			if (handled.at(i))
			{
				continue;
			}

			const auto& pair = source.at(i);
			const auto& [ start, length ] = pair;
			auto last = start + length - 1;

			bool handledThisCycle = false;

			if (start >= mapSour && last <= mapEnd)
			{
				// encapsulated
				result.push_back(std::make_pair(start + mapDest - mapSour, length));

				handledThisCycle = true;
			}
			else if (start < mapSour && last > mapEnd)
			{
				// overlapping both sides

				source.push_back(std::make_pair(start, mapSour - start));
				handled.push_back(false);

				result.push_back(std::make_pair(mapDest, mapLeng));

				source.push_back(std::make_pair(mapEnd + 1, last - mapEnd));
				handled.push_back(false);

				handledThisCycle = true;
			}
			else if (start <= mapSour && last <= mapEnd && last >= mapSour)
			{
				// overlap to the left
				auto length1 = mapSour - start;

				source.push_back(std::make_pair(start, length1));
				handled.push_back(false);

				result.push_back(std::make_pair(mapDest, length - length1));

				handledThisCycle = true;
			}
			else if (start >= mapSour && last >= mapEnd && start <= mapEnd)
			{
				// overlap to the right
				auto length1 = mapEnd + 1 - start;

				result.push_back(std::make_pair(start + mapDest - mapSour, length1));

				source.push_back(std::make_pair(mapEnd + 1, length - length1));
				handled.push_back(false);

				handledThisCycle = true;
			}

			if (handledThisCycle)
			{
				handled.at(i) = true;
			}
		}
	}

	for (std::size_t i = 0; i < source.size(); i++)
	{
		if (!handled.at(i))
		{
			result.push_back(source.at(i));
		}
	}


	return result;
}

std::size_t getMinSeed(
		std::vector<std::pair<std::size_t, std::size_t>> seeds)
{
	std::size_t minSeed = std::numeric_limits<std::size_t>::max();
	
	for (auto [ start, length ] : seeds)
	{
		minSeed = std::min(start, minSeed);
	}

	return minSeed;
}

std::string partOne(
		primary source)
{
	auto [ seedSource, maps ] = source;

	std::vector<std::pair<std::size_t, std::size_t>> seeds;

	for (auto seedLoc : seedSource)
	{
		seeds.push_back(std::make_pair(seedLoc, 1));
	}

	for (auto fullMap : maps)
	{
		seeds = applyMap(seeds, fullMap);
	}

	return std::to_string(getMinSeed(seeds));
}

std::string partTwo(
		primary source)
{
	auto [ seedSource, maps ] = source;

	std::vector<std::pair<std::size_t, std::size_t>> seeds;

	for (std::size_t i = 0; i < seedSource.size(); i += 2)
	{
		seeds.push_back(std::make_pair(seedSource.at(i), seedSource.at(i + 1)));
	}

	for (auto fullMap : maps)
	{
		seeds = applyMap(seeds, fullMap);
	}

	return std::to_string(getMinSeed(seeds));
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_05_input";

	auto parser = aocUtility::createWholesaleParserForFile<primary>(parse);

	aocUtility::executeWholesale<primary>(filename, parser, partOne, partTwo);

	return 0;
}
