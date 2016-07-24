#pragma once

#include <array>
#include <iostream>

#include "Point.h"

constexpr int Empty = 0;
constexpr int Black = 1;
constexpr int White = 2;
constexpr int TableSize = 15;

class Table
{
public:

	Table();
	~Table();

	bool play(const Point& p, const int who);
	void undo();

	bool check_win();
	void display(std::ostream& out = std::cout) const;

	bool check_point(const Point& p) const;
	const Point& last_point() const;
	const int& operator[](const Point& p) const;

private:
	std::array<std::array<int, TableSize>, TableSize> _table;
	Point _last_point;
	Point _last_but_one_point;

	bool _check_group(const Point&p, const int x_op, const int y_op);
};