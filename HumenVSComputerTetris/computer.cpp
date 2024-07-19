#include "computer.h"




void Computer::UpdateNextMove() 
{
	if (counter_next_move == 0)
	{
		SetBestRoute();
	}

	SetKeyPressed();
	counter_next_move++;
}

void Computer::SetKeyPressed() 
{
	switch (level)
	{
	case Game::BEST:
		keyPressed = best_route[counter_next_move];
		break;

	case Game::GOOD:
		ChooseMoveByLevel(40);
		break;

	case Game::NOVICE:
		ChooseMoveByLevel(10);
		break;
	}
}

void Computer::SetBestRoute()
{
	int distance = 0;

	if (myBoard.GetBombStatus())
	{
		if (level == Game::BEST)
		{
			distance = myBoard.SetBombDistance();
		}
		else
		{
			distance = 0;
		}
	}
	else
	{
		SetBestDestination();

		InsertRotationToBestRoute(best_destination.getRotation());

		best_destination.setDistance(*myBoard.GetShape());

		distance = best_destination.getDistance();
	}

	if (distance < 0)
	{

		for (int i = 0; i < -distance; ++i)
		{
			InsertKey((int)eKeys_L::LEFT_L, (int)eKeys_R::LEFT_L);
		}
	}
	else if (distance > 0)
	{
		for (int i = 0; i < distance; ++i)
		{
			InsertKey((int)eKeys_L::RIGHT_L, (int)eKeys_R::RIGHT_L);
		}
	}


}

void Computer::SetBestDestination()
{
	Shape temp = *this->myBoard.GetShape();
	best_destination = *this->myBoard.GetShape();
	best_destination.setLowestPoint();
	best_destination.InitRowsDeleted();
	curr_destination = best_destination;

	for (int k = (int)Shape::Degrees::deg0; k < (int)Shape::Degrees::deg360; k++)//Check all rotations of shape
	{
		int last_x_added = 0;
		int last_y_added = 0;

		if (k != (int)Shape::Degrees::deg0)
		{
			this->myBoard.GetShape()->setRotate(1);
			this->myBoard.GetShape()->changeRotation();
			curr_destination = *this->myBoard.GetShape();
			curr_destination.setRotation(k);
		}

		for (int i = 0; i < Board::HEIGHT; i++)
		{
			for (int j = 0; j < Board::WIDTH; j++)
			{
				if (this->myBoard.IsMoveOK(j - (Board::WIDTH / 2 - 1), i) && !(this->myBoard.IsMoveOK(j - (Board::WIDTH / 2 - 1), i + 1)) &&
					(this->myBoard.IsBlocked(j - (Board::WIDTH / 2 - 1), i - 1) == false && this->myBoard.IsBlocked(j - (Board::WIDTH / 2 - 1), i - 2) == false))//If shape can be there:
				{
					for (int k = 0; k < 4; k++)
					{
						curr_destination.getPoints()[k].setDirection(j - last_x_added, i - last_y_added);
						curr_destination.getPoints()[k].Move();
					}

					last_x_added = j;
					last_y_added = i;

					curr_destination.setRowsDeleted(myBoard);
					curr_destination.setLowestPoint();

					if (curr_destination.getRowsDeleted() > best_destination.getRowsDeleted())
					{
						best_destination = curr_destination;
						best_destination.setRotation(k);

					}
					else if ((curr_destination.getRowsDeleted() == best_destination.getRowsDeleted()) && (curr_destination.getLowestPoint() > best_destination.getLowestPoint()))
					{
						best_destination = curr_destination;
						best_destination.setRotation(k);
					}
				}
			}
		}
	}

	*this->myBoard.GetShape() = temp;
}

void Computer::InitBestRoute(int size) 
{
	for (int i = 0; i < size; i++)
	{
		best_route[i] = 0;
	}

	l_size = 0;
}

void Computer::InsertRotationToBestRoute(int rotation) 
{
	switch (rotation)
	{

	case (int)Shape::Degrees::deg90:

		InsertKey((int)eKeys_L::ROTATE_CLOCKWISE_L, (int)eKeys_R::ROTATE_CLOCKWISE_L);
		break;

	case (int)Shape::Degrees::deg180:

		for (int i = 0; i < (int)Shape::Degrees::deg180; i++, l_size++)
		{
			InsertKey((int)eKeys_L::ROTATE_CLOCKWISE_L, (int)eKeys_R::ROTATE_CLOCKWISE_L);
		}
		break;

	case (int)Shape::Degrees::deg270:

		InsertKey((int)eKeys_L::ROTATE_COUNTER_CLOCKWISE_L, (int)eKeys_R::ROTATE_COUNTER_CLOCKWISE_L);
		break;

	default:
		break;
	}
}

void Computer::InsertKey(int key_l, int key_r) 
{
	if (whoAmI == Board::LEFT)
		best_route[l_size] = key_l;
	else
		best_route[l_size] = key_r;

	l_size++;
}




void Computer::ChooseMoveByLevel(int frequency) 
{
	int num = (rand() % frequency) + 1;
	if (num == 1)
	{
		keyPressed = RandomMove();
	}
	else
	{
		keyPressed = best_route[counter_next_move];
	}
}

char Computer::RandomMove() const
{
	int move = (rand() % 5) + 1;

	switch (move)
	{
	case (int)Moves::LEFT:
		return ReturnRelevantKey((int)eKeys_L::LEFT_L, (int)eKeys_R::LEFT_L);
		break;

	case (int)Moves::RIGHT:
		return ReturnRelevantKey((int)eKeys_L::RIGHT_L, (int)eKeys_R::RIGHT_L);
		break;

	case (int)Moves::ROTATE_CLOCKWISE:
		return ReturnRelevantKey((int)eKeys_L::ROTATE_CLOCKWISE_L, (int)eKeys_R::ROTATE_CLOCKWISE_L);
		break;

	case (int)Moves::ROTATE_COUNTER_CLOCKWISE:
		return ReturnRelevantKey((int)eKeys_L::ROTATE_COUNTER_CLOCKWISE_L, (int)eKeys_R::ROTATE_COUNTER_CLOCKWISE_L);
		break;

	case (int)Moves::DROP:
		return ReturnRelevantKey((int)eKeys_L::DROP_L, (int)eKeys_R::DROP_L);
		break;
	}
}

int Computer::ReturnRelevantKey(int key_l, int key_r) const
{
	if (whoAmI == Board::LEFT)
		return key_l;
	else
		return key_r;
}

