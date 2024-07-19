#include "bomb.h"

void Bomb::moveToSide(int min_x, int min_y, int direction)
{
	setDirection(direction, 0);
	Draw(' ', min_x, min_y);
	Move();
	Draw('O', min_x, min_y);
	setDirection(0, 1);
}

void Bomb::MoveDown(int min_x, int min_y)
{
	Draw(' ', min_x, min_y);
	Move();
	Draw('O', min_x, min_y);
}
