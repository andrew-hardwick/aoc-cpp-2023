#pragma once

#include <iostream>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace aocUtility
{
	template<class T>
	void execute(
			std::string filename,
			std::function<std::vector<T>(std::string)> parser,
			std::function<std::string(std::vector<T>)> partOne,
			std::function<std::string(std::vector<T>)> partTwo)
	{
		// load data from file
		std::ifstream inf(filename);

		if (inf.fail())
		{
			return;
		}

		std::stringstream inss;
		inss << inf.rdbuf();
		std::string raw = inss.str();

		// parse
		std::vector<T> parsed = parser(raw);

		// execute (and print) part one
		std::cout << "Part 1: " << partOne(parsed) << "\n";

		// execute (and print) part two
		std::cout << "Part 2: " << partTwo(parsed) << "\n";
	}

	template <class T>
	std::function<std::vector<T>(std::string)> createParserForLine(
			std::function<T(std::string)> lineParser)
	{
		return [lineParser = std::move(lineParser)] (std::string source)
		{
			std::vector<T> result;

			std::stringstream inss(source);

			std::string line;

			while (std::getline(inss, line))
			{
				result.push_back(lineParser(line));
			}

			return result;
		};
	}

	template <class T>
	std::function<std::vector<T>(std::string)> createParserForChar(
			std::function<T(char)> charParser)
	{
		return [charParser = std::move(charParser)] (std::string source)
		{
			std::vector<T> result;

			for (auto c : source)
			{
				result.push_back(charParser(c));
			}

			return result;
		};
	}

	template <class T>
	std::function<std::vector<T>(std::string)> createParserForFile(
			std::function<std::vector<T>(const std::vector<std::string>)> fileParser)
	{
		return [fileParser = std::move(fileParser)] (std::string source)
		{
			std::vector<std::string> rawSource;

			std::stringstream inss(source);

			std::string line;

			while (std::getline(inss, line))
			{
				rawSource.push_back(line);
			}

			return fileParser(rawSource);
		};
	}
}
