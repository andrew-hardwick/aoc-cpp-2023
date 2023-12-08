#include "daybase.hpp"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <tuple>


typedef std::tuple<std::vector<uint>, uint, uint> primary;

uint parseType(
		std::vector<uint> hand,
		bool jokers_wild)
{
	std::sort(hand.begin(), hand.end());

	std::size_t maxMatchingCount = 0;
	std::size_t differentCards = 0;

	uint previousCard = 100;
	std::size_t matchingCount = 1;
	uint jokerCount = 0;

	for (auto card : hand)
	{
		if (card == 0)
		{
			jokerCount++;

			continue;
		}

		if (card != previousCard)
		{
			maxMatchingCount = std::max(matchingCount, maxMatchingCount);

			matchingCount =	1;

			differentCards += 1;
		}
		else
		{
			matchingCount++;
		}

		previousCard = card;
	}

	maxMatchingCount = std::max(matchingCount, maxMatchingCount);

	maxMatchingCount += jokerCount;

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
			
		case 1: // Five of a Kind
		default:
			type = 6;
			break;
	}

	return type;
}

uint parseCard(
		char c)
{
	if (c == 'T')
		return 10;
	if (c == 'J')
		return 11;
	if (c == 'Q')
		return 12;
	if (c == 'K')
		return 13;
	if (c == 'A')
		return 14;

	std::string temp { c };

	return std::stoul(temp);
}

primary parse(
		std::string line)
{
	std::string handSource = line.substr(0, 5);
	std::string bidSource = line.substr(6);

	uint bid = std::stoul(line.substr(6));

	std::vector<uint> hand;

	for (auto c : handSource)
	{
		hand.push_back(parseCard(c));
	}

	return std::make_tuple(hand, bid, 0);
}

std::vector<uint> zeroJokers(
		std::vector<uint> source)
{
	std::vector<uint> result;

	for (auto entry : source)
	{
		if (entry == 11)
		{
			result.push_back(0);
		}
		else
		{
			result.push_back(entry);
		}
	}

	return result;
}

bool compareHand(
		primary a,
		primary b)
{
	auto [ handA, bidA, typeA ] = a;
	auto [ handB, bidB, typeB ] = b;

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
			return charA < charB;
		}
	}

	return false;
}

std::string commonSolver(
		std::vector<primary> source)
{
	std::sort(source.begin(), source.end(), compareHand);

	std::size_t total = 0;

	for (std::size_t i = 0; i < source.size(); i++)
	{
		auto [ hand, bid, type ] = source.at(i);

		total += (i + 1) * bid;
	}
	
	return std::to_string(total);
}

std::string partOne(
		std::vector<primary> source)
{
	std::vector<primary> typedHands;

	for (auto [ hand, bid, _ ] : source)
	{
		typedHands.push_back(std::make_tuple(hand, bid, parseType(hand, false)));
	}

	return commonSolver(typedHands);
}

std::string partTwo(
		std::vector<primary> source)
{
	std::vector<primary> typedHands;

	for (auto [ hand, bid, _ ] : source)
	{
		auto adjustedHand = zeroJokers(hand);

		typedHands.push_back(std::make_tuple(adjustedHand, bid, parseType(adjustedHand, true)));
	}

	return commonSolver(typedHands);
}

int main(
		int argc,
		char** argv)
{
	auto filename = "input/2023_07_input";

	auto parser = aocUtility::createParserForLine<primary>(parse);

	aocUtility::execute<primary>(filename, parser, partOne, partTwo);

	return 0;
}
