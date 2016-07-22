#include "Point.h"

Point::Point()
{
}

Point::Point(int x_coo, int y_coo)
	: x(x_coo), y(y_coo)
{
}

Point::Point(char x_coo, int y_coo)
	: x(x_coo - 'A'), y(y_coo - 1)
{
}

Point::~Point()
{
}

const Point Point::operator+(const Point& r) const
{
	return Point(x + r.x, y + r.y);
}

const double Point::operator-(const Point& r) const
{
	return sqrt((x - r.x)*(x - r.x)+(y - r.y)*(y - r.y));
}

const Point & Point::operator+=(const Point & r)
{
	x += r.x; y += r.y;
	return *this;
}

const Point & Point::operator=(const Point & r)
{
	x = r.x; y = r.y;
	return *this;
}

std::ostream & operator<<(std::ostream & out, const Point & p)
{
	out << static_cast<char>(p.x + 'A') << " " << p.y + 1;
	return out;
}