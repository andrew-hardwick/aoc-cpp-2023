#pragma once

#include <iostream>


namespace aocUtility
{
	struct Point
	{
		/**
		 * normal constructor from values
		 */
		Point(
			int x,
			int y);

		/**
		 * strange constructor from string
		 * expects 'x,y' format
		 */
		Point(
			const std::string& source);

		int x = 0;
		int y = 0;

		double mag() const;

		bool isAdjacent(
				const Point& other) const;

		Point shiftX(
				int value) const;

		friend Point& operator+=(
				Point& self,
				const Point& other);

		friend std::ostream& operator<<(
				std::ostream& os,
				const Point& p);

		friend bool operator==(
				const Point& p1,
				const Point& p2);

		friend bool operator!=(
				const Point& p1,
				const Point& p2);

		friend bool operator<(
				const Point& p1,
				const Point& p2);

		friend bool operator>(
				const Point& p1,
				const Point& p2);

		friend Point operator-(
				Point p1,
				const Point& p2);

		friend Point operator+(
				Point p1,
				const Point& p2);
	};
}

