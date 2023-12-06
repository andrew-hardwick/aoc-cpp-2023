#include "daybase.hpp"
#include "stringFunctions.h"

#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>


typedef std::vector<std::pair<std::size_t, std::size_t>> primary;

std::vector<std::size_t> parseSingleLine(
		const std::string& line)
{
	auto numSource = aocUtility::string::splitByDelimiter(line, ":")[1];

	numSource = aocUtility::string::replace(numSource, "  ", " ");
	numSource = aocUtility::string::replace(numSource, "  ", " ");
	numSource = aocUtility::string::replace(numSource, "  ", " ");
	numSource = aocUtility::string::replace(numSource, "  ", " ");

	numSource = aocUtility::string::trim(numSource);

	auto splitNumSource = aocUtility::string::splitByDelimiter(numSource, " ");

	std::vector<std::size_t> result;

	for (auto e : splitNumSource)
	{
		result.push_back(std::stoul(e));
	}

	return result;
}

primary parse(
		const std::vector<std::string>& file)
{
	std::vector<std::pair<std::size_t, std::size_t>> result;

	auto timeSource = file.at(0);
	auto distanceSource = file.at(1);

	auto time = parseSingleLine(timeSource);
	auto distance = parseSingleLine(distanceSource);

	if (time.size() != distance.size())
	{
		throw std::invalid_argument("Input arrays must match");
	}

	for (std::size_t i = 0 ; i < time.size(); i++)
	{
		result.push_back(std::make_pair(time.at(i), distance.at(i)));
	}

	return result;
}

int calculateWinCount(
		double t,
		double d)
{
		double discriminantRoot = std::sqrt(std::pow(t, 2.) - 4. * d);

		double preciseLowerBound = (t - discriminantRoot) / 2.;
		double preciseUpperBound = (t + discriminantRoot) / 2.;

		int lowerBound = (int) preciseLowerBound; // Really the lower bound is one more than this
		int upperBound = (int) preciseUpperBound;

		if (upperBound == preciseUpperBound)
		{
			upperBound--;
		}

		int waysToWin = upperBound - lowerBound;

		return waysToWin;
}

std::string partOne(
		primary source)
{
	int product = 1;

	for (auto [ t, d ] : source)
	{
		product *= calculateWinCount(t, d);
	}

	return std::to_string(product);
}

std::string partTwo(
		primary source)
{
	std::size_t time = 0;
	std::size_t timeOrder = 0;

	std::size_t distance = 0;
	std::size_t distanceOrder = 0;

	for (auto it = source.crbegin(); it != source.crend(); it++)
	{
		auto [ t, d ] = *it;

		time += t * (std::size_t)std::pow(10, timeOrder);
		distance += d * (std::size_t)std::pow(10, distanceOrder);

		timeOrder += (std::size_t)std::floor(std::log10(t)) + 1;
		distanceOrder += (std::size_t)std::floor(std::log10(d)) + 1;
	}

	int waysToWin = calculateWinCount(time, distance);

	return std::to_string(waysToWin);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_06_input";

	auto parser = aocUtility::createWholesaleParserForFile<primary>(parse);

	aocUtility::executeWholesale<primary>(filename, parser, partOne, partTwo);

	return 0;
}
