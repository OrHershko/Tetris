#pragma once
#include "player.h"

class Human: public Player
{

public:

	Human(Board& board, int me): Player(board,me){} //C'tor

};

