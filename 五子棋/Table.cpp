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
	_last_but_one_point = _last_point;
	_last_point = p;

	return true;
}

void Table::undo()
{
	_table[_last_but_one_point.x][_last_but_one_point.y] = Empty;
	_table[_last_point.x][_last_point.y] = Empty;
}

bool Table::check_win()
{
	for (int i = 0; i != 5; ++i) {
		if (_check_group(_last_point + Point(0, -i), 0, 1)
			|| _check_group(_last_point + Point(i, -i), -1, 1)
			|| _check_group(_last_point + Point(i, 0), -1, 0)
			|| _check_group(_last_point + Point(-i, -i), 1, 1))
			return true;
	}
	return false;
}

bool Table::_check_group(const Point & p, const int x_op, const int y_op)
{
	bool flag = false;
	int last_color = _table[_last_point.x][_last_point.y];
	Point now_p = p;

	for (int i = 0; i != 5; ++i, now_p += Point(x_op, y_op)) {
		if (now_p.x > TableSize - 1 || now_p.x < 0
			|| now_p.y > TableSize - 1 || now_p.y < 0)
			continue;
		if (_table[now_p.x][now_p.y] == last_color) {
			flag = true;
		}
		else {
			flag = false;
			break;
		}
	}
	return flag;
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