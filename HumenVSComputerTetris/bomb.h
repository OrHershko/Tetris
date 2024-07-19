#pragma once
#include "point.h"

class Bomb : public Point
{
public:

	void moveToSide(int min_x, int min_y, int direction); //Draws the bomb in it's new location

	void MoveDown(int min_x, int min_y);// Draws the bomb downwards it's current location

};

