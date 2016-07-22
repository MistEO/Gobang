#include <iostream>
#include <algorithm>
#include <vector>

#include "AI.h"

AI::AI(const Table& t)
	:_table(t)
{
}


AI::~AI()
{
}

Point AI::calc()
{
	return _calc_score();
}

const Point AI::_calc_score()
{
	std::pair<Point, int> max_score;
	max_score.first = _table.last_point() + Point(0, 1);
	max_score.second = 0;

	std::array<Point, 8> point_temp;
	point_temp.fill(_table.last_point());
	for (int i = 1; i != 6; ++i) {
		point_temp[0] += Point(0, i);
		point_temp[1] += Point(-i, i);
		point_temp[2] += Point(-i, 0);
		point_temp[3] += Point(-i, -i);
		point_temp[4] += Point(0, -i);
		point_temp[5] += Point(i, -i);
		point_temp[6] += Point(i, 0);
		point_temp[7] += Point(i, i);

		for (int j = 0; j != 8; ++j) {
			int now_point_score = _calc_point_score(point_temp[j]);
			if (max_score.second < now_point_score) {
				max_score.first = point_temp[j];
				max_score.second = now_point_score;
			}
		}

	}

	return max_score.first;
}

int AI::_calc_point_score(const Point& p)
{
	if (!_table.check_point(p)) {
		return Virtual;
	}

	int score = 0;
	score += _calc_group_score(p, 0, 1);
	score += _calc_group_score(p, -1, 1);
	score += _calc_group_score(p, -1, 0);
	score += _calc_group_score(p, -1, -1);
	score += _calc_group_score(p, 0, -1);
	score += _calc_group_score(p, 1, -1);
	score += _calc_group_score(p, 1, 0);
	score += _calc_group_score(p, 1, 1);

	return score;
}

int AI::_calc_group_score(const Point& p, const int x_op, const int y_op) const
{
	int black_count = 0, white_count = 0;
	Point now_p = p;

	for (int i = 0; i != 5; ++i) {
		if (_table[now_p] == Black) {
			++black_count;
		}
		else if (_table[now_p] == White) {
			++white_count;
		}
		if (white_count != 0 && black_count != 0)
			break;

		now_p += Point(x_op, y_op);
		if (now_p.x > TableSize - 1 || now_p.x < 0
			|| now_p.y > TableSize - 1 || now_p.y < 0)
			break;
	}
	if (black_count == 0 && white_count == 0)
		return Blank;
	else if (black_count == 1 && white_count <= black_count)
		return B;
	else if (black_count == 2 && white_count <= black_count)
		return BB;
	else if (black_count == 3 && white_count <= black_count)
		return BBB;
	else if (black_count == 4 && white_count <= black_count)
		return BBBB;
	else if (black_count <= white_count && white_count == 1)
		return W;
	else if (black_count <= white_count && white_count == 2)
		return WW;
	else if (black_count <= white_count && white_count == 3)
		return WWW;
	else if (black_count <= white_count && white_count == 4)
		return WWWW;
	else if (black_count >= 1 && white_count >= 1)
		return Polluted;
	else
		return Virtual;

}