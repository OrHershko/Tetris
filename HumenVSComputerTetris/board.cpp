#include "board.h"
#include <iostream>
using namespace std;


int Board::saver_data_matrix_left[HEIGHT][WIDTH];

int Board::saver_data_matrix_right[HEIGHT][WIDTH];

Shape Board::shapeTemp_left;

Shape Board::shapeTemp_right;

Bomb Board::bombTemp_left;

Bomb Board::bombTemp_right;

bool Board::bombastic_round_left;

bool Board::bombastic_round_right;



Board::Board(int min_x, int min_y)
{

	this->min_x = min_x;
	this->min_y = min_y;


}

void Board::PrintBoard() const
{

	for (int col = min_x; col < WIDTH + min_x; col++)
	{
		gotoxy(col, min_y - 1);
		cout << "-";

		gotoxy(col, HEIGHT + min_y);
		cout << "-";
	}

	for (int row = min_y - 1; row <= HEIGHT + min_y; row++)
	{
		gotoxy(min_x - 1, row);
		cout << "|";

		gotoxy(WIDTH + min_x, row);
		cout << "|";
	}


}



bool Board::IsMoveOK(int diff_x, int diff_y)
{
	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{

		if ((currShape.getPoints()[i].getX() + WIDTH / 2 - 1 + diff_x < 0) || (currShape.getPoints()[i].getX() + WIDTH / 2 - 1 + diff_x > 11))
		{
			return false;
		}

		if ((currShape.getPoints()[i].getY() + diff_y >= HEIGHT) ||
			(data_matrix[currShape.getPoints()[i].getY() + diff_y][currShape.getPoints()[i].getX() + WIDTH / 2 - 1 + diff_x] == 1))
		{
			return false;
		}

		if (currShape.getPoints()[i].getY() < 0)
		{
			return false;
		}

	}


	return true;

}


void Board::UpdateMatrix(Shape* shape)
{
	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{
		data_matrix[shape->getPoints()[i].getY()][shape->getPoints()[i].getX() + WIDTH / 2 - 1] = 1;
	}
}

void Board::setValueToMatrix(int value, int row, int col)
{
	data_matrix[row][col] = value;
}



void Board::printSomewhereOnBoard(char ch, int row, int col) const
{
	gotoxy(col + min_x, row + min_y);
	cout << ch;
}


bool Board::isRotatePossible(int direction)
{
	Shape temp(currShape);

	currShape.setRotate(direction);
	currShape.changeRotation();

	if (IsMoveOK(0, 0) == false)
	{
		currShape = temp;

		return false;
	}

	currShape = temp;

	return true;
}






void Board::DeleteFullRow()
{
	for (int i = 0; i < Board::HEIGHT; i++)
	{
		for (int j = 0; j < Board::WIDTH; j++)
		{
			if (getValueFromMatrix(i, j) == 0) //If there is a zero in the line, stop checking the line.
			{
				break;
			}

			if (j == Board::WIDTH - 1) //If we reached the end of the line, there is a full row.
			{
				for (int k = 0; k < Board::WIDTH; k++) //delete the row.
				{
					setValueToMatrix(0, i, k);
				}

				for (int l = i; l >= 1; l--) //Copy each row to the row below and prints it.
				{
					for (int k = 0; k < Board::WIDTH; k++)
					{
						setValueToMatrix(getValueFromMatrix(l - 1, k), l, k);

						if (getValueFromMatrix(l, k) == 0)
						{
							printSomewhereOnBoard(' ', l, k);
						}
						else if (getValueFromMatrix(l, k) == 1)
						{
							printSomewhereOnBoard('#', l, k);
						}
					}
				}

				for (int k = 0; k < Board::WIDTH; k++)
				{
					setValueToMatrix(0, 0, k);
				}
			}
		}
	}
}


void Board::initializeMatrix()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			data_matrix[i][j] = 0;
		}
	}
}

void Board::PrintByMatrix() const
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (data_matrix[i][j] == 1)
			{
				printSomewhereOnBoard('#', i, j);
			}
		}
	}
}


void Board::saveDataLeft()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			saver_data_matrix_left[i][j] = data_matrix[i][j];
		}
	}

	if (bombastic_round == true)
	{
		bombTemp_left = bomb;
		bombastic_round_left = true;
	}
	else
	{
		shapeTemp_left = currShape;
		bombastic_round_left = false;
	}
}

void Board::saveDataRight()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			saver_data_matrix_right[i][j] = data_matrix[i][j];
		}
	}
	if (bombastic_round == true)
	{
		bombTemp_right = bomb;
		bombastic_round_right = true;
	}
	else
	{
		shapeTemp_right = currShape;
		bombastic_round_right = false;

	}
}


void Board::LoadDataLeft()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			data_matrix[i][j] = saver_data_matrix_left[i][j];
		}
	}

	if (bombastic_round_left == true)
	{
		bomb = bombTemp_left;
	}
	else
	{
		currShape = shapeTemp_left;
	}

	bombastic_round = bombastic_round_left;
}

void Board::LoadDataRight()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			data_matrix[i][j] = saver_data_matrix_right[i][j];
		}
	}

	if (bombastic_round_right == true)
	{
		bomb = bombTemp_right;
	}
	else
	{
		currShape = shapeTemp_right;
	}

	bombastic_round = bombastic_round_right;
}

void Board::printYouLose() const
{
	gotoxy(min_x, min_y + HEIGHT / 2 - 2);
	cout << "************";
	gotoxy(min_x, min_y + HEIGHT / 2 - 1);
	cout << "            ";
	gotoxy(min_x, min_y + HEIGHT / 2);
	cout << "  YOU LOSE! ";
	gotoxy(min_x, min_y + HEIGHT / 2 + 1);
	cout << "            ";
	gotoxy(min_x, min_y + HEIGHT / 2 + 2);
	cout << "************";
}

void Board::printYouWin() const
{
	gotoxy(min_x, min_y + HEIGHT / 2 - 2);
	cout << "************";
	gotoxy(min_x, min_y + HEIGHT / 2 - 1);
	cout << "            ";
	gotoxy(min_x, min_y + HEIGHT / 2);
	cout << "  YOU WIN!  ";
	gotoxy(min_x, min_y + HEIGHT / 2 + 1);
	cout << "            ";
	gotoxy(min_x, min_y + HEIGHT / 2 + 2);
	cout << "************";
}


void Board::SetBombStatus(bool status)
{
	bombastic_round = status;
}


int Board::SetBombDistance() 
{
	for (int i = 0; i < Board::HEIGHT; i++)
	{
		for (int j = 0; j < Board::WIDTH; j++)
		{
			if (IsMoveBombOk(j - (Board::WIDTH / 2 - 1), i) && !(IsMoveBombOk(j - (Board::WIDTH / 2 - 1), i + 1)))
			{
				return j - (Board::WIDTH / 2 - 1);
			}
		}
	}
}

void Board::MoveBombToSide(int side) 
{
	if (IsMoveBombOk(side, 0))
	{
		bomb.moveToSide(min_x, min_y, side);
	}
}


void Board::DropBombDown()
{
	while (IsMoveBombOk(0, Shape::DOWN) == true)
	{
		bomb.MoveDown(min_x, min_y);

		Sleep(10);
	}
}

bool Board::IsMoveBombOk(int diff_x, int diff_y) const
{

	if ((bomb.getX() + WIDTH / 2 - 1 + diff_x < 0) || (bomb.getX() + WIDTH / 2 - 1 + diff_x > 11))
	{
		return false;
	}

	if ((bomb.getY() + diff_y >= HEIGHT) ||
		(data_matrix[bomb.getY() + diff_y][bomb.getX() + WIDTH / 2 - 1 + diff_x] == 1))
	{
		return false;
	}

	if (bomb.getY() < 0)
	{
		return false;
	}

	return true;
}


void Board::BombActivated() 
{
	Bomb temp = bomb;

	for (int j = -4; j <= 4; j++) //Delete the blocks in the bomb radius
	{
		if (bomb.getY() + j >= 0 && bomb.getY() + j < HEIGHT)
		{
			bomb.setDirection(0, j);
			bomb.Move();

			for (int i = -4; i <= 4; i++)
			{
				if ((bomb.getX() + WIDTH / 2 - 1 + i >= 0) && (bomb.getX() + WIDTH / 2 - 1 + i <= 11))
				{
					printSomewhereOnBoard(' ', bomb.getY(), bomb.getX() + WIDTH / 2 - 1 + i);
					setValueToMatrix(0, bomb.getY(), bomb.getX() + WIDTH / 2 - 1 + i);
				}
			}
			bomb = temp;
		}
	}

	for (int l = bomb.getY(); l >= 1; l--) //Drop down the blocks above the bomb
	{
		for (int i = -4 ; i <= 4; i++)
		{
			if ((bomb.getX() + WIDTH / 2 - 1 + i >= 0) && (bomb.getX() + WIDTH / 2 - 1 + i <= 11))
			{
				setValueToMatrix(getValueFromMatrix(l - 1, bomb.getX() + WIDTH / 2 - 1 + i), l, bomb.getX() + WIDTH / 2 - 1 + i);

				if (getValueFromMatrix(l, bomb.getX() + WIDTH / 2 - 1 + i) == 0)
				{
					printSomewhereOnBoard(' ', l, bomb.getX() + WIDTH / 2 - 1 + i);
				}
				else if (getValueFromMatrix(l, bomb.getX() + WIDTH / 2 - 1 + i) == 1)
				{
					printSomewhereOnBoard('#', l, bomb.getX() + WIDTH / 2 - 1 + i);
				}
			}
		}
	}
}

void Board::CheckAndMoveToSideMyShape(int side)
{
	if (IsMoveOK(side, 0))
	{
		currShape.moveToSide(min_x, min_y, side);
	}
}


void Board::CheckAndDropMyShape()
{
	while (IsMoveOK(0, Shape::DOWN) == true)
	{
		currShape.moveDown(min_x, min_y);

		Sleep(10);
	}
}


void Board::RotateMyShape(int direction)
{
	if (currShape.getMyShape() == CUBE)
	{
		return;
	}

	currShape.Draw(' ', min_x, min_y);

	if (isRotatePossible(direction) == false)
	{
		currShape.Draw('#', min_x, min_y);
	}
	else
	{
		currShape.RotateToSide(min_x, min_y, direction);
	}
}


void Board::InitBomb()
{
	bomb.init(0, 0);
	bomb.setDirection(0, 1);
}


void Board::DrawBomb()
{
	bomb.Draw('O', min_x, min_y);
}


void Board::MoveBombDown()
{
	bomb.MoveDown(min_x, min_y);
}

bool Board::IsBlocked(int diff_x, int diff_y)
{
	for (int i = 0; i < Shape::NUM_OF_CUBES; i++)
	{
		if (data_matrix[currShape.getPoints()[i].getY() + diff_y][currShape.getPoints()[i].getX() + WIDTH / 2 - 1 + diff_x] == 1)
		{
			return true;
		}

		if (currShape.getPoints()[i].getY() + diff_y < 0)
		{
			return true;
		}
	}
	return false;
}

