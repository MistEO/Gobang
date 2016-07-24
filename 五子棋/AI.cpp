#include <iostream>
#include <algorithm>
#include <utility>

#include "AI.h"

AI::AI(const Table& t)
	:_table(t)
{
}


AI::~AI()
{
}

const Point AI::calc()
{
	return _calc_score();
}

const Point AI::_calc_score()
//计算每个点分数，返回最大分数且距离刚才落子位置最近的点
{
	std::pair<Point, int> max_score;	//坐标&分数
	max_score.first = Point(0, 0);
	max_score.second = 0;
	double distance = 22.5;

	for (int i = 0; i != 15; ++i) {
		for (int j = 0; j != 15; ++j) {
			for (int k = 0; k != 8; ++k) {
				int now_point_score = _calc_point_score(Point(i, j));
				if (max_score.second < now_point_score			//当前点的分数更大
					|| (max_score.second == now_point_score		//分数相等但距离更近
						&& distance > Point(i, j) - _table.last_point())) {
					max_score.first = Point(i, j);
					max_score.second = now_point_score;
					distance = Point(i, j) - _table.last_point();
				}
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
	for (int i = 0; i != 5; ++i) {
		score += _calc_group_score(p + Point(0, -i), 0, 1);
		score += _calc_group_score(p + Point(i, -i), -1, 1);
		score += _calc_group_score(p + Point(i, 0), -1, 0);
		score += _calc_group_score(p + Point(-i, -i), 1, 1);
	}
	return score;
}

int AI::_calc_group_score(const Point& p, const int x_op, const int y_op) const
{
	int black_count = 0, white_count = 0;
	Point now_p = p;

	for (int i = 0; i != 5; ++i, now_p += Point(x_op, y_op)) {
		if (now_p.x > TableSize - 1 || now_p.x < 0
			|| now_p.y > TableSize - 1 || now_p.y < 0)
			continue;
		if (_table[now_p] == Black) {
			if (white_count != 0) {
				return Polluted;
			}
			++black_count;
		}
		else if (_table[now_p] == White) {
			if (black_count != 0) {
				return Polluted;
			}
			++white_count;
		}
	}

	if (black_count == 0 && white_count == 0)
		return Blank;
	else if (black_count == 1)
		return B;
	else if (black_count == 2)
		return BB;
	else if (black_count == 3)
		return BBB;
	else if (black_count == 4)
		return BBBB;
	else if (white_count == 1)
		return W;
	else if (white_count == 2)
		return WW;
	else if (white_count == 3)
		return WWW;
	else if (white_count == 4)
		return WWWW;
	else
		return Virtual;

}