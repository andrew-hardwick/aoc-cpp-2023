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
		 * can be wrapped in parenthesis: '(x,y)'
		 * can have or not have a space 'x, y' or 'x,\ty'
		 * can have whitespace around or not '  x, y ' or '\tx,y'
		 */
		static Point From(
			const std::string& source);

		const int x = 0;
		const int y = 0;

		double mag() const;

		bool isAdjacent(
				const Point& other) const;

		Point shiftX(
				int value) const;

		friend Point operator+=(
				const Point& p1,
				const Point& p2);

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
				const Point& p1,
				const Point& p2);

		friend Point operator+(
				const Point& p1,
				const Point& p2);
	};
}

