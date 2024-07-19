#pragma once
#include "destination.h"
#include "board.h"
#include "game.h"
#include <iostream>
#include "player.h"


class Computer : public Player
{

	int counter_next_move = 0;

	int best_route[Board::WIDTH] = { 0 };

	int l_size = 0;

	Destination best_destination;

	Destination curr_destination;

	int level;


public:

	enum class Moves{LEFT = 1 , RIGHT, ROTATE_CLOCKWISE, ROTATE_COUNTER_CLOCKWISE, DROP};


	Computer(Board& board, int me, int level) : Player(board, me) , level(level) {} // C'tor

	void UpdateNextMove(); //Sets the best route and\or the next move of the computer

	void setCounter(int num) { counter_next_move = num; } // Sets the counter to num

	void SetKeyPressed() override; //Sets the keyPressed by inserting the random moves frequency depends on the computer's level

	void SetBestRoute();  //Finds the ideal moves and insert them into the "best route" array

	void SetBestDestination(); //Finds the best destination for a shape in a current round

	void InitBestRoute(int size); // Initilazes the "best route" array and sets the logical size to 0

	void InsertRotationToBestRoute(int rotation); // Insert the relevat rotation button to the "best route" array

	void InsertKey(int key_l, int key_r); // Inserts the move key depends on the relevant board to the "best route" array

	void ChooseMoveByLevel(int frequency); //Makes random moves depends on the level of the computer

	char RandomMove() const; //Select a random move

	int ReturnRelevantKey(int key_l, int key_r) const; // Returns the move key depends on the relevant board 

};

