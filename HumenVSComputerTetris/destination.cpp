#include "destination.h"

void Destination::operator=( Shape& shape)
{
	for (int i = 0; i < NUM_OF_CUBES; i++)
	{
		this->arr_points[i] = shape.getPoints()[i];
	}

	this->rotation = shape.getRotate();
}

void Destination::setRowsDeleted(Board& board) 
{
	rowsDeleted = 0;

	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{
		board.setValueToMatrix(1, arr_points[i].getY(), arr_points[i].getX());
	}

	for (int i = 0; i < Board::HEIGHT; i++)
	{

		for (int j = 0; j < Board::WIDTH; j++)
		{

			if (board.getValueFromMatrix(i, j) == 0) //If there is a zero in the line, stop checking the line.
			{
				break;
			}

			if (j == Board::WIDTH - 1) //If we reached the end of the line, there is a full row.
			{
				++rowsDeleted;
			}
		}
	}

	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{
		board.setValueToMatrix(0, arr_points[i].getY(), arr_points[i].getX());
	}
}

void Destination::setLowestPoint()
{
	lowestPoint = arr_points[0].getY();

	for (int i = 1; i < Shape::NUM_OF_CUBES; i++)
	{
		if (arr_points[i].getY() > lowestPoint)
			lowestPoint = arr_points[i].getY();
	}
}

void Destination::setRotation(int degree) 
{
	rotation = degree;
}

void Destination::InitRowsDeleted() 
{
	rowsDeleted = 0;
}


void Destination::setDistance(Shape orgShape) 
{
	orgShape.setRotate(rotation);
	orgShape.changeRotation();

	distance_from_org = arr_points[0].getX() - orgShape.getPoints()[0].getX() - 5;
}
