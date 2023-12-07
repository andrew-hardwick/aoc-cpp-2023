#include "daybase.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>


typedef std::tuple<std::string, uint, uint> primary;

uint parseType(
		std::string hand)
{
	std::sort(hand.begin(), hand.end());

	std::size_t maxMatchingCount = 0;
	std::size_t differentCards = 0;

	char previousCard = ' ';
	std::size_t matchingCount = 1;

	for (auto card : hand)
	{
		if (card != previousCard)
		{
			maxMatchingCount = std::max(matchingCount, maxMatchingCount);

			differentCards += 1;
		}
		else
		{
			matchingCount++;
		}

		previousCard = card;
	}

	std::size_t type = 0;

	switch (differentCards)
	{
		case 5: // High Card
			type = 0;
			break;
			
		case 4: // Pair
			type = 1;
			break;
			
		case 3: // Two Pair or Three of a Kind
			type = maxMatchingCount == 2 ? 2 : 3;
			break;
			
		case 2: // Full House or Four of a Kind
			type = maxMatchingCount == 3 ? 4 : 5;
			break;
			
		case 1:
		default:
			type = 6;
			break;
			
	}

	return type;
}

primary parse(
		std::string line)
{
	std::string hand = line.substr(0, 5);
	std::string bidSource = line.substr(6);

	uint bid = std::stoul(line.substr(6));
	uint type = parseType(hand);

	return std::make_tuple(hand, type, bid);
}

bool compareHandPartOne(
		primary a,
		primary b)
{
	auto [ handA, typeA, _a ] = a;
	auto [ handB, typeB, _b ] = b;

	if (typeA != typeB)
	{
		return typeA < typeB;
	}

	if (handA.size() != handB.size())
	{
		throw std::domain_error("Error, hand sizes do not match");
	}

	for (std::size_t i = 0; i < handA.size(); i++)
	{
		auto charA = handA.at(i);
		auto charB = handB.at(i);

		if (charA != charB)
		{
			return charA > charB;
		}
	}

	return false;
}

std::string partOne(
		std::vector<primary> source)
{
	std::sort(source.begin(), source.end(), compareHandPartOne);

	std::size_t total = 0;

	for (std::size_t i = 0; i < source.size(); i++)
	{
		auto [ _0, _1, bid ] = source.at(i);

		std::cout << (i + 1) << " " << bid << "\n";

		total += (i + 1) * bid;
	}

	return std::to_string(total);
}

std::string partTwo(
		std::vector<primary> source)
{
	return "nonimpl";
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_07_test1";

	auto parser = aocUtility::createParserForLine<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
