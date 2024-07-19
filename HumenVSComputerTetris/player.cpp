#include "player.h"


void Player::MakeBombMove(Board& board_L, Board& board_R)
{
	switch (keyPressed) //Game progress according to user input.
	{
	case (int)eKeys_L::LEFT_L:
	case (int)eKeys_L::LEFT_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.MoveBombToSide(Shape::LEFT);
		break;

	case (int)eKeys_R::LEFT_L:
	case (int)eKeys_R::LEFT_U:

		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.MoveBombToSide(Shape::LEFT);
		break;

	case (int)eKeys_L::RIGHT_L:
	case (int)eKeys_L::RIGHT_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.MoveBombToSide(Shape::RIGHT);
		break;

	case (int)eKeys_R::RIGHT_L:
	case (int)eKeys_R::RIGHT_U:

		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.MoveBombToSide(Shape::RIGHT);
		break;

	case (int)eKeys_L::DROP_L:
	case (int)eKeys_L::DROP_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.DropBombDown();
		break;

	case (int)eKeys_R::DROP_L:
	case (int)eKeys_R::DROP_U:

		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.DropBombDown();
		break;
	}

	keyPressed = 0;
}



void Player::MakeMove(Board& board_L, Board& board_R) 
{

	switch (keyPressed) 
	{
	case (int)eKeys_L::LEFT_L:
	case (int)eKeys_L::LEFT_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.CheckAndMoveToSideMyShape(Shape::LEFT);
		break;

	case (int)eKeys_R::LEFT_L:
	case (int)eKeys_R::LEFT_U:

		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.CheckAndMoveToSideMyShape(Shape::LEFT);
		break;

	case (int)eKeys_L::RIGHT_L:
	case (int)eKeys_L::RIGHT_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.CheckAndMoveToSideMyShape(Shape::RIGHT);
		break;

	case (int)eKeys_R::RIGHT_L:
	case (int)eKeys_R::RIGHT_U:

		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.CheckAndMoveToSideMyShape(Shape::RIGHT);
		break;

	case (int)eKeys_L::ROTATE_CLOCKWISE_L:
	case (int)eKeys_L::ROTATE_CLOCKWISE_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.RotateMyShape(Shape::CLOCKWISE);
		break;

	case (int)eKeys_L::ROTATE_COUNTER_CLOCKWISE_L:
	case (int)eKeys_L::ROTATE_COUNTER_CLOCKWISE_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.RotateMyShape(Shape::COUNTER_CLOCKWISE);
		break;

	case (int)eKeys_R::ROTATE_CLOCKWISE_L:
	case (int)eKeys_R::ROTATE_CLOCKWISE_U:


		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.RotateMyShape(Shape::CLOCKWISE);
		break;

	case (int)eKeys_R::ROTATE_COUNTER_CLOCKWISE_L:
	case (int)eKeys_R::ROTATE_COUNTER_CLOCKWISE_U:

		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.RotateMyShape(Shape::COUNTER_CLOCKWISE);
		break;

	case (int)eKeys_L::DROP_L:
	case (int)eKeys_L::DROP_U:

		if (whoAmI == Game::RIGHT_BOARD)
			break;

		board_L.CheckAndDropMyShape();
		break;

	case (int)eKeys_R::DROP_L:
	case (int)eKeys_R::DROP_U:

		if (whoAmI == Game::LEFT_BOARD)
			break;

		board_R.CheckAndDropMyShape();
		break;
	}

	keyPressed = 0;
}

void Player::SetKeyPressed(int keyPressed)
{
	this->keyPressed = keyPressed;
}