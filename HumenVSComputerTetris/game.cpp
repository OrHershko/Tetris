
#include "game.h"
#include "computer.h"
#include "human.h"
#include <iostream>
using namespace std;


void Game::SetStateOfGame(int stateOfGame)
{
	this->stateOfGame = stateOfGame;
}

void Game::StartGame()
{
	Board board_L(40, 2);
	Board board_R(70, 2);

	Init(board_L, board_R);

	Player* player_L; 
	Player* player_R;  

	CreatePlayers(&player_L, &player_R, board_L, board_R);

	bool isPlayerL_Human = IsPlayerHuman(player_L);
	bool isPlayerR_Human = IsPlayerHuman(player_R);

	while (true)
	{
		board_L.DeleteFullRow();
		board_R.DeleteFullRow();

		if (board_L.GetBombStatus())
		{
			board_L.DrawBomb();
		}
		else
		{
			board_L.GetShape()->Draw('#', board_L.GetMinX(), board_L.GetMinY());
		}

		if (board_R.GetBombStatus())
		{
			board_R.DrawBomb();
		}
		else
		{
			board_R.GetShape()->Draw('#', board_R.GetMinX(), board_R.GetMinY());
		}

		Sleep(300);

		if (_kbhit())
		{
			int keyPressed = _getch();

			if (isPlayerL_Human == true)
			{
				player_L->SetKeyPressed(keyPressed);
			}

			if (isPlayerR_Human == true)
			{
				player_R->SetKeyPressed(keyPressed);
			}

			if (IsGamePaused(board_L, board_R, keyPressed))
			{
				return;
			}
		}

		CheckIfComputerAndUpdateNextMove(player_L);
		CheckIfComputerAndUpdateNextMove(player_R);

		if (board_L.GetBombStatus())
		{
			player_L->MakeBombMove(board_L, board_R);
		}
		else
		{
			player_L->MakeMove(board_L, board_R);
		}

		if (board_R.GetBombStatus())
		{
			player_R->MakeBombMove(board_L, board_R);
		}
		else
		{
			player_R->MakeMove(board_L, board_R);
		}
	
		if (!IsThereNextRound(board_R, board_L, player_L) || !IsThereNextRound(board_L, board_R, player_R))
		{
			break;
		}
	}

	delete player_L;
	delete player_R;
}



bool Game::IsGameOver(Board& winner, Board& loser) 
{
	if (loser.GetShape()->isReachedLine(0) == true)
	{
		loser.printYouLose();
		winner.printYouWin();
		SetStateOfGame(GAME_FINISHED);
		return true;
	}
	else
		return false;
}

bool Game::IsThereNextRound(Board& board1, Board& board2, Player* player) 
{
	if (board2.GetBombStatus() == false)
	{
		if (board2.IsMoveOK(0, Shape::DOWN) == true)
		{
			board2.GetShape()->moveDown(board2.GetMinX(), board2.GetMinY());
		}
		else
		{
			board2.UpdateMatrix(board2.GetShape());

			if (IsGameOver(board1, board2))
			{
				return false;
			}

			CreateNextRound(board2, player);
		}
	}
	else
	{
		if (board2.IsMoveBombOk(0, Shape::DOWN) == true)
		{
			board2.MoveBombDown();
		}
		else
		{
			board2.BombActivated();

			CreateNextRound(board2, player);
		}
	}

	return true;
}

void Game::Init(Board& boardL, Board& boardR) 
{
	boardL.PrintBoard();
	boardR.PrintBoard();

	if (stateOfGame == GAME_DIDNT_START)
	{
		boardL.initializeMatrix();
		boardR.initializeMatrix();

		boardL.GetShape()->RandomShape();
		boardR.GetShape()->RandomShape();

		boardL.GetShape()->init();
		boardR.GetShape()->init();
	}
	else if (stateOfGame == GAME_STARTED_NO_WINNER)
	{
		boardL.LoadDataLeft();
		boardR.LoadDataRight();

		boardL.PrintByMatrix();
		boardR.PrintByMatrix();
	}
}

bool Game::IsGamePaused(Board& board1, Board& board2, int keyPressed)
{
	if (keyPressed == Board::ESC)
	{
		board1.saveDataLeft();
		board2.saveDataRight();
		SetStateOfGame(GAME_STARTED_NO_WINNER);
		return true;
	}

	return false;
}



void Game::CreateNextRound(Board& board, Player* player)
{
	int chance_for_bomb = (rand() % 100) + 1;

	if (chance_for_bomb <= 5)
	{
		board.InitBomb();
		board.SetBombStatus(true);
	}
	else
	{
		board.GetShape()->RandomShape();
		board.GetShape()->init();
		board.SetBombStatus(false);
	}

	Computer* comp = dynamic_cast<Computer*>(player);

	if (comp)
	{
		comp->setCounter(0);
		comp->InitBestRoute(Board::WIDTH);
	}

	while (_kbhit() == true) //to clean extra presses between old and new shape.
	{
		int keyPressed = _getch();
	}
}


void Game::SetWhoPlays(int whoplays)
{
	this->whoPlays = whoplays;
}

void Game::CreatePlayers(Player** player_L, Player** player_R, Board& boardL, Board& boardR)
{
	if (whoPlays == HumanVSHuman)
	{
		*player_L = new Human(boardL, LEFT_BOARD);
		*player_R = new Human(boardR, RIGHT_BOARD);

	}
	else if (whoPlays == HumanVSComputer) 
	{
		*player_L = new Human(boardL, LEFT_BOARD);
		*player_R = new Computer(boardR, RIGHT_BOARD, right_level);

	}
	else
	{
		*player_L = new Computer(boardL, LEFT_BOARD, left_level);
		*player_R = new Computer(boardR, RIGHT_BOARD, right_level);

	}
}


void Game::CheckIfHumanAndSetKey(Player* player, int keyPressed) 
{
	Human* temp = dynamic_cast<Human*>(player);

	if (temp) {

		temp->SetKeyPressed(keyPressed);
	}
}

void Game::CheckIfComputerAndUpdateNextMove(Player* player)
{
	Computer* temp = dynamic_cast<Computer*>(player);

	if (temp) {

		temp->UpdateNextMove();
	}
}

bool Game::IsPlayerHuman(Player* player) 
{
	Human* temp = dynamic_cast<Human*>(player);

	if (temp) 
		return true;
	else 
		return false;
}


void Game::ChooseLevel()
{
	char level;

	if (whoPlays == HumanVSComputer)
	{
		system("cls");
		PrintAndSetLevels("the");
	}
	else if (whoPlays == ComputerVSComputer)
	{
		system("cls");
		PrintAndSetLevels("left");
		system("cls");
		PrintAndSetLevels("right");
	}
}

void Game::PrintAndSetLevels(const char* word) 
{
	char level = 0;

	gotoxy(40, 2);
	cout << "Please choose " << word << " computer's level:" << endl;
	PrintLevelOptions();

	while (true)
	{
		if (_kbhit())
		{
			level = _getch();
		}

		if (level == BEST || level == BEST_U || level == GOOD || level == GOOD_U || level == NOVICE || level == NOVICE_U)
		{
			if (strcmp("the", word) == 0 || strcmp("right", word) == 0)
			{
				SetRightLevel(level);
			}
			else
			{
				SetLeftLevel(level);
			}

			break;
		}
	}
}

void Game::PrintLevelOptions() const
{
	gotoxy(40, 3);
	cout << "(a) BEST";
	gotoxy(40, 4);
	cout << "(b) GOOD";
	gotoxy(40, 5);
	cout << "(c) NOVICE";
}

void Game::SetLeftLevel(char level)
{
	switch (level)
	{
	case BEST:
	case BEST_U:
		left_level = BEST;
		break;
	case GOOD:
	case GOOD_U:
		left_level = GOOD;
		break;
	case NOVICE:
	case NOVICE_U:
		left_level = NOVICE;
		break;
	default:
		break;
	}
}

void Game::SetRightLevel(char level)
{
	switch (level)
	{
	case BEST:
	case BEST_U:
		right_level = BEST;
		break;
	case GOOD:
	case GOOD_U:
		right_level = GOOD;
		break;
	case NOVICE:
	case NOVICE_U:
		right_level = NOVICE;
		break;
	default:
		break;
	}
}