#pragma once

#include <string>
#include <vector>


namespace aocUtility { namespace string
{
	std::vector<std::string> splitByDelimiter(
			std::string source,
			std::string delimiter);

	std::vector<std::string> splitByDelimiter(
			std::string source,
			char delimiter);

	std::string replace(
			std::string source,
			std::string target,
			std::string replacement);

	std::vector<std::string> getSubstringsOfLength(
			std::string source,
			std::size_t length);

	std::string& ltrim(
			std::string& s);

	std::string& rtrim(
			std::string& s);

	std::string& trim(
			std::string& s);
} }

