#include "shape.h"



void Shape::RandomShape()
{
	myShape = (rand() % NUM_OF_SHAPES) + 1;

	switch (myShape)
	{

	case (int)Tetrominos::tetromino1:
		org_x[0] = 0;
		org_x[1] = 0;
		org_x[2] = 0;
		org_x[3] = 0;
		org_y[0] = 0;
		org_y[1] = 1;
		org_y[2] = 2;
		org_y[3] = 3;
		break;

	case (int)Tetrominos::tetromino2:
		org_x[0] = 0;
		org_x[1] = 1;
		org_x[2] = 0;
		org_x[3] = 1;
		org_y[0] = 0;
		org_y[1] = 0;
		org_y[2] = 1;
		org_y[3] = 1;
		break;

	case (int)Tetrominos::tetromino3:
		org_x[0] = 0;
		org_x[1] = 0;
		org_x[2] = 0;
		org_x[3] = 1;
		org_y[0] = 0;
		org_y[1] = 1;
		org_y[2] = 2;
		org_y[3] = 2;
		break;

	case (int)Tetrominos::tetromino4:
		org_x[0] = 1;
		org_x[1] = 1;
		org_x[2] = 1;
		org_x[3] = 0;
		org_y[0] = 0;
		org_y[1] = 1;
		org_y[2] = 2;
		org_y[3] = 2;
		break;

	case (int)Tetrominos::tetromino5:
		org_x[0] = 0;
		org_x[1] = 1;
		org_x[2] = 1;
		org_x[3] = 2;
		org_y[0] = 0;
		org_y[1] = 0;
		org_y[2] = 1;
		org_y[3] = 1;
		break;

	case (int)Tetrominos::tetromino6:
		org_x[0] = 0;
		org_x[1] = 1;
		org_x[2] = 2;
		org_x[3] = 1;
		org_y[0] = 0;
		org_y[1] = 0;
		org_y[2] = 0;
		org_y[3] = 1;
		break;

	case (int)Tetrominos::tetromino7:
		org_x[0] = 0;
		org_x[1] = 1;
		org_x[2] = 1;
		org_x[3] = 2;
		org_y[0] = 1;
		org_y[1] = 1;
		org_y[2] = 0;
		org_y[3] = 0;
		break;

	}
}

void Shape::Draw(char ch, int min_x, int min_y) const
{
	for (int i = 0; i < NUM_OF_CUBES; i++)
	{
		arr_points[i].Draw(ch, min_x, min_y);

	}
}

void Shape::init()
{
	for (int i = 0; i < NUM_OF_CUBES; i++)
	{
		arr_points[i].init(org_x[i], org_y[i]);
		postRotate_x[i] = org_x[i];
		postRotate_y[i] = org_y[i];
	}
}

void Shape::Move(int min_x, int min_y)
{
	for (int i = 0; i < NUM_OF_CUBES; i++)
	{
		arr_points[i].Draw(' ', min_x, min_y);

	}

	for (int i = 0; i < NUM_OF_CUBES; i++)
	{

		arr_points[i].Move();
		arr_points[i].Draw('#', min_x, min_y);
	}
}


void Shape::setRotate(int direction)
{
	rotate += direction;

	if (rotate == (int)Degrees::deg360)
	{
		rotate = (int)Degrees::deg0;
	}
	if (rotate == (int)Degrees::degMinus90)
	{
		rotate = (int)Degrees::deg270;
	}

	switch (rotate)
	{
	case (int)Degrees::deg0:

		for (int i = 0; i < NUM_OF_CUBES; i++)
		{
			preRotate_x[i] = postRotate_x[i];

			preRotate_y[i] = postRotate_y[i];

			postRotate_x[i] = org_x[i];

			postRotate_y[i] = org_y[i];
		}

		break;

	case (int)Degrees::deg90:

		for (int i = 0; i < NUM_OF_CUBES; i++)
		{
			preRotate_x[i] = postRotate_x[i];

			preRotate_y[i] = postRotate_y[i];

			postRotate_x[i] = org_y[i];

			postRotate_y[i] = -org_x[i];

		}

		break;

	case (int)Degrees::deg180:

		for (int i = 0; i < NUM_OF_CUBES; i++)
		{

			preRotate_x[i] = postRotate_x[i];

			preRotate_y[i] = postRotate_y[i];

			postRotate_x[i] = -org_x[i];

			postRotate_y[i] = -org_y[i];

		}

		break;


	case (int)Degrees::deg270:

		for (int i = 0; i < NUM_OF_CUBES; i++)
		{
			preRotate_x[i] = postRotate_x[i];

			preRotate_y[i] = postRotate_y[i];

			postRotate_x[i] = -org_y[i];

			postRotate_y[i] = org_x[i];

		}

		break;
	}
}


void Shape::changeRotation()
{
	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{
		arr_points[i].setRotation(preRotate_x[i], preRotate_y[i],
			postRotate_x[i], postRotate_y[i]);
	}
}


void Shape::changeDirection(int diff_x, int diff_y)
{
	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{
		arr_points[i].setDirection(diff_x, diff_y);
	}
}

bool Shape::isReachedLine(int line) const
{
	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{
		if (arr_points[i].getY() == line)
		{
			return true;
		}

		return false;
	}
}

void Shape::moveToSide(int min_x, int min_y, int direction)
{
	changeDirection(direction, 0);
	Draw(' ', min_x, min_y);
	Move(min_x, min_y);
	Draw('#', min_x, min_y);
	changeDirection(0, 1);
}

void Shape::RotateToSide(int min_x, int min_y, int direction)
{
	setRotate(direction);
	changeRotation();
	Draw('#', min_x, min_y);
}

void Shape::moveDown(int min_x, int min_y)
{
	Draw(' ', min_x, min_y);
	Move(min_x, min_y);
	Draw('#', min_x, min_y);
}
