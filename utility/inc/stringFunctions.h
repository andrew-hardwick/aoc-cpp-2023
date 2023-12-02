#pragma once

#include <string>
#include <vector>


namespace aocUtility { namespace string
{
	std::vector<std::string> splitByDelimiter(
			std::string source,
			std::string delimiter);

	std::string replace(
			std::string source,
			std::string target,
			std::string replacement);
} }

