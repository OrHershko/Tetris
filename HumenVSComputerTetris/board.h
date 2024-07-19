#pragma once
#include "general.h"
#include "shape.h"
#include "bomb.h"
#include <Windows.h>


class Board
{
public:

	static constexpr int WIDTH = 12;
	static constexpr int HEIGHT = 18;
	static constexpr int LEFT = -1;
	static constexpr int RIGHT = 1;

private:

	int min_x;
	int min_y;

	Shape currShape;
	Bomb bomb;

	bool bombastic_round = false;

	static int saver_data_matrix_left[HEIGHT][WIDTH];
	static int saver_data_matrix_right[HEIGHT][WIDTH];
	static Shape shapeTemp_left;
	static Shape shapeTemp_right;
	static Bomb bombTemp_left;
	static Bomb bombTemp_right;
	static bool bombastic_round_left;
	static bool bombastic_round_right;

	int data_matrix[HEIGHT][WIDTH];

public:

	static constexpr int ESC = 27;
	static constexpr int CUBE = 2;


	Board(int min_x, int min_y); //C'tor

	void PrintBoard() const; //Prints the board frame.

	Shape* GetShape() { return &currShape; }

	Bomb& GetBomb() { return bomb; }

	int SetBombDistance(); // Calculte the distance between the original bomb and the destination bomb

	void MoveBombToSide(int side); // If the move is possible, move the bomb

	void DropBombDown(); //Drop the bomb to the lowest point possible

	bool IsMoveBombOk(int diff_x, int diff_y) const; // Return true if the bomb move is possible

	void BombActivated(); //Delete the blocks in the radius of the bomb

	void initializeMatrix(); // Initialize the data matrix with zeros.

	int GetMinX() const { return min_x; }

	int GetMinY() const { return min_y; }

	bool GetBombStatus() const { return bombastic_round; }

	void SetBombStatus(bool status); //Sets the bomb status

	void setValueToMatrix(int value, int row, int col); //Set value to the given row and col.

	int getValueFromMatrix(int row, int col) const { return data_matrix[row][col]; }

	bool IsMoveOK(int diff_x, int diff_y); //Return true if a shape movement is between the borders and there isn't another shape on that location.

	bool isRotatePossible(int direction); //Return true if the rotation is possible.

	void UpdateMatrix(Shape* shape); //Set ones to the data matrix where the shape stop its movement.

	void printSomewhereOnBoard(char ch, int x, int y) const; //Prints a char on a given location.

	void DeleteFullRow(); //If there is a full row, deletes it and drop down the lines above it.

	void PrintByMatrix() const; //Prints the shapes on the board according to the data matrix.

	void saveDataLeft(); //Copy the data matrix to the left saver matrix.

	void saveDataRight(); //Copy the data matrix to the right saver matrix.

	void LoadDataLeft(); //Copy the left saver matrix to data matrix.

	void LoadDataRight(); //Copy the right saver matrix to data matrix.

	void printYouLose() const; //Prints on the losing board.

	void printYouWin() const; //Prints on the winning board.

	void CheckAndMoveToSideMyShape(int side); //If the move is possible, move the shape

	void CheckAndDropMyShape();//Drop the shape to the lowest point possible

	void RotateMyShape(int direction); //If the rotation is possible, rotate the shape

	void InitBomb();//Initialize the board's bomb

	void DrawBomb();//Draw the board's bomb

	void MoveBombDown();//Move the board's bomb down

	bool IsBlocked(int diff_x, int diff_y);//returns true if there is a block above a destenation

};

enum class eKeys_L {
	LEFT_L = 'a', RIGHT_L = 'd', ROTATE_CLOCKWISE_L = 's', ROTATE_COUNTER_CLOCKWISE_L = 'w', DROP_L = 'x'
	, LEFT_U = 'A', RIGHT_U = 'D', ROTATE_CLOCKWISE_U = 'S', ROTATE_COUNTER_CLOCKWISE_U = 'W', DROP_U = 'X'
};

enum class eKeys_R {
	LEFT_L = 'j', RIGHT_L = 'l', ROTATE_CLOCKWISE_L = 'k', ROTATE_COUNTER_CLOCKWISE_L = 'i', DROP_L = 'm'
	, LEFT_U = 'J', RIGHT_U = 'L', ROTATE_CLOCKWISE_U = 'K', ROTATE_COUNTER_CLOCKWISE_U = 'I', DROP_U = 'M'
};
