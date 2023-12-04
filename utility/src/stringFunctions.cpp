#include "stringFunctions.h"

#include <sstream>

namespace aocUtility { namespace string
{
	std::vector<std::string> splitByDelimiter(
			std::string source,
			std::string delimiter)
	{
		std::vector<std::string> result;

		const std::size_t delimiterLength = delimiter.size();
		
		auto distance = source.find(delimiter);

		while (distance != std::string::npos)
		{
			result.push_back(source.substr(0, distance));
	
			source = source.substr(distance + delimiterLength);

			distance = source.find(delimiter);
		}

		result.push_back(source);

		return result;
	}

	std::vector<std::string> splitByDelimiter(
			std::string source,
			char delimiter)
	{
		std::string delimiterString { delimiter };

		return splitByDelimiter(source, delimiterString);
	}

	std::string replace(
			std::string source,
			std::string target,
			std::string replacement)
	{
		auto split = splitByDelimiter(source, target);

		if (split.size() == 1)
		{
			return source;
		}

		std::stringstream builder;

		std::vector<std::string> partial(split.begin(), split.end() - 1);

		for (auto e : partial)
		{
			builder << e;
			builder << replacement;
		}

		builder << *(split.end() - 1);

		return builder.str();
	}

	std::vector<std::string> getSubstringsOfLength(
			std::string source,
			std::size_t length)
	{
		std::vector<std::string> result;

		while (source.size() > length)
		{
			auto portion = source.substr(0, length);

			result.push_back(portion);

			source = source.substr(length);
		}
		
		result.push_back(source);

		return result;
	}
	
	const char* ws = " \t\n\r\f\v";

	std::string& rtrim(
			std::string& s)
	{
			s.erase(s.find_last_not_of(ws) + 1);
			return s;
	}

	std::string& ltrim(
			std::string& s)
	{
			s.erase(0, s.find_first_not_of(ws));
			return s;
	}

	std::string& trim(
			std::string& s)
	{
			return ltrim(rtrim(s));
	}
} }
