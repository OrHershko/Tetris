#include "menu.h"
#include <iostream>
using namespace std;


void Menu::MainMenu()
{
	int pressedKey = 0;

	Game game;

	PrintMenu();

	while (true)
	{
		if (_kbhit())
		{
			pressedKey = _getch();
		}
		else
		{
			pressedKey = 0;
		}

		switch (pressedKey)
		{
		case HUMAN_VS_HUMAN:

			game.SetWhoPlays(Game::HumanVSHuman);
			StartNewGame(game);
			break;

		case HUMAN_VS_COMPUTER:

			game.SetWhoPlays(Game::HumanVSComputer);
			game.ChooseLevel();
			StartNewGame(game);
			break;

		case COMPUTER_VS_COMPUTER:

			game.SetWhoPlays(Game::ComputerVSComputer);
			game.ChooseLevel();
			StartNewGame(game);
			break;

		case INSTRUCTIONS:

			system("cls");
			PrintInstructions();

			if (game.GetStateOfGame() == Game::GAME_DIDNT_START)
			{
				system("cls");
				PrintMenu();
			}
			else if (game.GetStateOfGame() == Game::GAME_STARTED_NO_WINNER)
			{
				system("cls");
				PrintPausedMenu();
			}
			break;

		default:
			break;
		}

		if (pressedKey == RESUME_GAME && game.GetStateOfGame() == Game::GAME_STARTED_NO_WINNER)
		{
			system("cls");
			game.StartGame();

			if (game.GetStateOfGame() == Game::GAME_STARTED_NO_WINNER)
			{
				system("cls");
				PrintPausedMenu();
			}
		}

		if (game.GetStateOfGame() == Game::GAME_FINISHED)
		{
			PressKeyToContinue();
			game.SetStateOfGame(Game::GAME_DIDNT_START);
			system("cls");
			PrintMenu();
		}

		if (pressedKey == EXIT)
		{
			system("cls");
			break;
		}
	}
}

void Menu::PrintInstructions() const
{
	cout << "In the game, you must arrange a sequence of small shapes, called Tetraminos, into complete lines. " << endl;
	cout << "As each line is completed, it will disappear from the screen. " << endl;
	cout << "Tetraminos fall from the top of the play field to the bottom. " << endl;
	cout << "Each Tetramino is made up of four blocks, arranged into seven different patterns. " << endl << endl;
	cout << "Every round there is a small chance to get a bomb." << endl;
	cout << "A bomb is a single square block represented by the letter 'O'. " << endl;
	cout << "When a bomb reaches its position on top of any other square, " << endl;
	cout << "it explodes and all squares that are in a block distance of 4 squares disappear" << endl << endl;
	cout << "This is a two player game, each with his own board. " << endl;
	cout << "The game is over when one of the players Tetriminos reaching the top, " << endl;
	cout << "that player lose the game, and the other player wins." << endl << endl;


	cout << "Controls for left board:" << endl;
	cout << "LEFT: a or A" << endl;
	cout << "RIGHT: d or D" << endl;
	cout << "ROTATE CLOCKWISE: s or S" << endl;
	cout << "ROTATE COUNTERCLOCKWISE: w or W" << endl;
	cout << "DROP: x or X" << endl << endl;


	cout << "Controls for right board:" << endl;
	cout << "LEFT: j or J" << endl;
	cout << "RIGHT: l or L" << endl;
	cout << "ROTATE CLOCKWISE: k or K" << endl;
	cout << "ROTATE COUNTERCLOCKWISE: i or I" << endl;
	cout << "DROP: m or M" << endl << endl;

	PressKeyToContinue();
}

void Menu::PrintMenu() const
{
	gotoxy(40, 2);

	cout << "*********************************************";

	gotoxy(45, 3);

	cout << "ARE YOU READY TO PLAY SOME TETRIS?!";

	gotoxy(40, 4);

	cout << "*********************************************";

	gotoxy(45, 6);

	cout << "(1) Start a new game - Human vs Human";

	gotoxy(45, 7);

	cout << "(2) Start a new game - Human vs Computer";

	gotoxy(45, 8);

	cout << "(3) Start a new game - Computer vs Computer";

	gotoxy(45, 9);

	cout << "(8) Instructions and Keys";

	gotoxy(45, 10);

	cout << "(9) Exit";
}


void Menu::PrintPausedMenu() const
{
	gotoxy(40, 2);

	cout << "**********************************";

	gotoxy(48, 3);

	cout << "The game is paused";

	gotoxy(40, 4);

	cout << "**********************************";

	gotoxy(45, 6);

	cout << "(1) Start a new game - Human vs Human";

	gotoxy(45, 7);

	cout << "(2) Start a new game - Human vs Computer";

	gotoxy(45, 8);

	cout << "(3) Start a new game - Computer vs Computer";

	gotoxy(45, 9);

	cout << "(4) Resume the paused game";

	gotoxy(45, 10);

	cout << "(8) Instructions and Keys";

	gotoxy(45, 11);

	cout << "(9) Exit";
}


void Menu::PressKeyToContinue() const
{
	gotoxy(0, 28);
	cout << "Press ESC to go back to the menu...";

	while (true)
	{
		if (_kbhit())
		{
			char keyPressed = _getch();

			if (keyPressed == ESC)
				break;
		}
	}
}

void Menu:: StartNewGame(Game& game) 
{
	game.SetStateOfGame(Game::GAME_DIDNT_START);
	system("cls");
	game.StartGame();

	if (game.GetStateOfGame() == Game::GAME_STARTED_NO_WINNER)
	{
		system("cls");
		PrintPausedMenu();
	}
}
