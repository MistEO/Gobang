#pragma once
#include <iostream>
class Point
{
public:
	Point();
	Point(int x_coo, int y_coo);
	Point(char x_coo, int y_coo);

	~Point();

	const Point operator+(const Point& r) const;	//����λ��
	const double operator-(const Point& r) const;	//�������

	const Point& operator+=(const Point&r);			//����λ��

	const Point& operator=(const Point& r);

	friend std::ostream& operator<<(std::ostream& out, const Point& p);
	

	int x;
	int y;
};

