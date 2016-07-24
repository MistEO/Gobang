#pragma once
#include <iostream>
class Point
{
public:
	Point();
	Point(int x_coo, int y_coo);
	Point(char x_coo, int y_coo);

	~Point();

	const Point operator+(const Point& r) const;	//计算位移
	const double operator-(const Point& r) const;	//计算距离

	const Point& operator+=(const Point&r);			//自增位移

	const Point& operator=(const Point& r);

	friend std::ostream& operator<<(std::ostream& out, const Point& p);
	

	int x;
	int y;
};

