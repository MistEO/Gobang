#include "Table.h"



Table::Table()
	:_last_point(7, 7)
{
	for (auto &i : _table) {
		i.fill(Empty);
	}
}


Table::~Table()
{
}

bool Table::play(const Point& p, const int who)
{
	if (!check_point(p)) {
		return false;
	}
	_table[p.x][p.y] = who;
	_last_point = p;

	return true;
}

bool Table::check_win()
{
	if (_check_group(_last_point, 0, 1)
		|| _check_group(_last_point, 1, 1)
		|| _check_group(_last_point, 1, 0)
		|| _check_group(_last_point, -1, 1)) {
		return true;
	}
	return false;
}

bool Table::_check_group(const Point & p, const int x_op, const int y_op)
{
	int count = 0;
	int last_color = _table[p.x][p.y];
	Point now_point = p + Point(-4 * x_op, -4 * y_op);
	for (int i = 0; i != 10; ++i) {
		if (x_op == -1) {
			if (now_point.x - 1 < 0 || now_point.y < 0
				|| now_point.x > TableSize - 1
				|| now_point.y + y_op > TableSize - 1) {
				continue;
			}
		}
		else if (now_point.x < 0 || now_point.y < 0
			|| now_point.x + x_op > TableSize - 1
			|| now_point.y + y_op > TableSize - 1) {
			continue;
		}

		if (_table[now_point.x][now_point.y] == last_color) {
			if (++count == 5) {
				return true;
			}
		}
		else {
			count = 0;
		}
		now_point += Point(x_op, y_op);
	}
	return false;
}

void Table::display(std::ostream & out) const
{
	for (int i = 0; i != 9; ++i) {
		out << "  " << i + 1;
	}
	for (int i = 0; i != 6; ++i) {
		out << "  " << i;
	}
	out << std::endl;
	char temp = 'A';
	for (auto i : _table) {
		out << temp++;
		for (auto j : i) {
			switch (j)
			{
			case Empty:
				out << "  .";
				break;
			case Black:
				out << "  X";
				break;
			case White:
				out << "  O";
				break;
			default:
				break;
			}
		}
		out << std::endl;
	}
}

const Point & Table::last_point() const
{
	return _last_point;
}

const int& Table::operator[](const Point& p) const
{
	return _table[p.x][p.y];
}

inline bool Table::check_point(const Point& p) const
{
	if (p.x < 0 || p.x > TableSize - 1 || p.y < 0 || p.y > TableSize - 1) {
		return false;
	}
	if (_table[p.x][p.y] != Empty) {
		return false;
	}

	return true;
}