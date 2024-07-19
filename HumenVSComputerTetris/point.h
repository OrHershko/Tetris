#pragma once
#include "general.h"

class Point
{
	int x;
	int y;
	int diff_x = 0;
	int diff_y = 1;


public:

	void init(int x, int y); //Sets the initial value of a coordinate.

	void Draw(char ch, int min_x, int min_y) const; //Prints a char in a given location.

	void Move(); //Adds the movment difference to the coordinate.

	int getX() const { return x; }

	int getY() const { return y; }

	void setDirection(int diff_x, int diff_y); //Changes the movment difference.

	void setRotation(int preRotateX, int preRotateY, int rotated_x, int rotated_y); //change the coordinates by the wanted degree.

};



