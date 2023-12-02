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

	std::string replace(
			std::string source,
			std::string target,
			std::string replacement)
	{
		auto split = splitByDelimiter(source, target);

		std::stringstream builder;

		std::vector<std::string> partial(split.begin(), split.end() - 1);

		for (auto e : split)
		{
			builder << e;
			builder << replacement;
		}

		builder << *(split.end() - 1);

		return builder.str();
	}
} }
