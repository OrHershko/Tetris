#include "point.h"
#include <iostream>
using namespace std;


void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
}


void Point::Draw(char ch, int min_x, int min_y) const
{

	gotoxy(x + min_x + 5, y + min_y);
	cout << ch;

}

void Point::Move()
{
	x += diff_x;
	y += diff_y;
}

void Point::setDirection(int diff_x, int diff_y)
{
	this->diff_x = diff_x;
	this->diff_y = diff_y;
}

void Point::setRotation(int preRotateX, int preRotateY, int rotated_x, int rotated_y)
{
	x = x - preRotateX + rotated_x;
	y = y - preRotateY + rotated_y;
}

