#include "point.h"

#include "stringFunctions.h"
#include <cmath>

namespace aocUtility
{
	Point::Point(
		int x,
		int y)
			: x(x), y(y)
	{}

	Point Point::From(
		const std::string& source)
	{
		std::string cleanSource = aocUtility::string::replace(source, "(","");
		cleanSource = aocUtility::string::replace(cleanSource, ")","");
		cleanSource = aocUtility::string::trim(cleanSource);

		auto splitSource = aocUtility::string::splitByDelimiter(cleanSource, ',');

		auto x = std::stod(splitSource[0]);
		auto y = std::stod(splitSource[1]);

		return Point(x, y);
	}

	double Point::mag() const
	{
		return pow(pow(x, 2) + pow(y, 2), 0.5);
	}

	bool Point::isAdjacent(
			const Point& other) const
	{
		int deltaX = x - other.x;
		int deltaY = y - other.y;

		int deltaXMag = abs(deltaX);
		int deltaYMag = abs(deltaY);

		if (deltaXMag == 0 && deltaYMag == 0)
		{
			return false;
		}

		if (deltaXMag <= 1 && deltaYMag <= 1)
		{
			return true;
		}

		return false;
	}

	Point Point::shiftX(
			int value) const
	{
		return Point(x + value, y);
	}

	Point operator+=(
			const Point& p1,
			const Point& p2)
	{
		auto x = p1.x + p2.x;
		auto y = p1.y + p2.y;

		return Point(x, y);
	}

	std::ostream& operator<<(
			std::ostream& os,
			const Point& p)
	{
		os << "(" << p.x << ", " << p.y << ")";
		return os;
	}

	bool operator==(
			const Point& p1,
			const Point& p2)
	{
		return p1.x == p2.x && p1.y == p2.y;
	}

	bool operator!=(
			const Point& p1,
			const Point& p2)
	{
		return p1.x != p2.x || p1.y != p2.y;
	}

	bool operator<(
			const Point& p1,
			const Point& p2)
	{
		if (p1.x != p2.x) return p1.x < p2.x;
		return p1.y < p2.y;
	}

	bool operator>(
			const Point& p1,
			const Point& p2)
	{
		if (p1.x != p2.x) return p1.x > p2.x;
		return p1.y > p2.y;
	}

	Point operator-(
			const Point& p1,
			const Point& p2)
	{
		return Point(p1.x - p2.x, p1.y - p2.y);
	}

	Point operator+(
			const Point& p1,
			const Point& p2)
	{
		return Point(p1.x + p2.x, p1.y + p2.y);
	}
}
