#pragma once

#include "Table.h"

class AI
{

	static constexpr int Blank = 7,
		B = 35,
		BB = 800,
		BBB = 15000,
		BBBB = 800000,
		W = 15,
		WW = 400,
		WWW = 1800,
		WWWW = 100000,
		Virtual = 0,
		Polluted = 0;
public:
	AI(const Table& t);
	~AI();

	Point calc();

private:
	const Table& _table;

	const Point _calc_score();
	int _calc_point_score(const Point& p);
	int _calc_group_score(const Point& p, const int x_op,  const int y_op) const;
};

