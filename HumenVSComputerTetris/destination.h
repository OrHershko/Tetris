#pragma once

#include "point.h"
#include "shape.h"
#include "board.h"


class Destination
{
public:
	static constexpr int NUM_OF_CUBES = 4;

private:

	int rotation = 0; //Current degree of shape.
	Point arr_points[NUM_OF_CUBES]; //shape is made of four cubes.
	int rowsDeleted = 0;
	int lowestPoint = 0;
	int overlaps = 0;
	int distance_from_org = 0;

public:

	void operator=(Shape& shape); //  operator "=" between shape and destination

	void setRotation(int degree); //Sets the rotation to the wanted degree

	void setRowsDeleted(Board& board); //Calcultes and Sets the number of rows deleted by the current destination

	void setLowestPoint();//Calcultes and Sets the lowest point of the current destination

	void setDistance(Shape orgShape); //Rotate the shape and calculte the distanse fron the original shape

	void InitRowsDeleted(); // Initilaizes rowsDeleted to 0

	int getDistance() const { return distance_from_org; }

	int getRowsDeleted() const { return rowsDeleted; }

	int getLowestPoint() const { return lowestPoint; }

	int getRotation() const { return rotation; }

	Point* getPoints() { return arr_points; }

};

