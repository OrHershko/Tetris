#pragma once

#include "point.h"
#include <stdlib.h> 
#include <time.h>	

class Shape
{
public:

	static constexpr int NUM_OF_CUBES = 4;
	static constexpr int LEFT = -1;
	static constexpr int RIGHT = 1;
	static constexpr int CLOCKWISE = 1;
	static constexpr int COUNTER_CLOCKWISE = -1;
	static constexpr int DOWN = 1;
	static constexpr int NUM_OF_SHAPES = 7;

	enum class Tetrominos { tetromino1 = 1, tetromino2, tetromino3, tetromino4, tetromino5, tetromino6, tetromino7 };

	enum class Degrees { degMinus90 = -1, deg0, deg90, deg180, deg270, deg360 };

private:

	int myShape;

	//Original coordinates of a shape.

	int org_x[NUM_OF_CUBES];
	int org_y[NUM_OF_CUBES];

	//The coordinates of the shape before rotation.

	int preRotate_x[NUM_OF_CUBES];
	int preRotate_y[NUM_OF_CUBES];

	//The coordinates of the shape after rotation.

	int postRotate_x[NUM_OF_CUBES];
	int postRotate_y[NUM_OF_CUBES];

	int rotate = 0; //Current degree of shape.

	Point arr_points[NUM_OF_CUBES]; //Each shape is made of four cubes.

public:

	void RandomShape(); //Select a random shape.

	void init(); //initialize a shape by its original coordinates.

	void Draw(char ch, int min_x, int min_y) const; //Prints the shape.

	void Move(int min_x, int min_y); //Moves the shape by deleting the shape and reprints it at the next location.

	Point* getPoints() { return arr_points; }

	int getMyShape() const { return myShape; }

	int* getOrgX() { return org_x; }

	int* getOrgY() { return org_y; }

	void setRotate(int direction); //By using math formula it changes the coordinates according to the wanted diraction.

	int getRotate() const { return rotate; }

	int* getPreRotateX() { return preRotate_x; }

	int* getPreRotateY() { return preRotate_y; }

	int* getPostRotateX() { return postRotate_x; }

	int* getPostRotateY() { return postRotate_y; }

	void changeDirection(int diff_x, int diff_y); //Change the shape diraction by changing each point diraction.

	void changeRotation();//Change the shape rotation by changing each point rotation.

	bool isReachedLine(int line) const; //Return true if a shape reached to the top of the board.

	void moveToSide(int min_x, int min_y, int direction); //Moves the shape left/right.

	void RotateToSide(int min_x, int min_y, int direction); //Rotates the shape clockwise/counter clockwise.

	void moveDown(int min_x, int min_y); //Move the shape down.


};



