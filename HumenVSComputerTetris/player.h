#pragma once

#include "board.h"
#include "game.h"


class Player
{

protected:

	int whoAmI = 0;
	Board& myBoard;
	int keyPressed = 0;

	Player(Board& board, int me) : myBoard(board), whoAmI(me) {} //C'tor


public:
	
	void MakeMove(Board& board_L, Board& board_R); //Make the current shape move depends on the keyPressed

	void MakeBombMove(Board& board_L, Board& board_R); //Make the bomb move depends on the keyPressed

	virtual void SetKeyPressed() {}; 

	int GetKeyPressed() const { return keyPressed; }	

	void SetKeyPressed(int keyPressed); // Sets the keyPressed

};

