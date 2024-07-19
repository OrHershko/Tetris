#pragma once
#include "general.h"
#include "game.h"
#include <Windows.h>
#include <conio.h> 
#include "string.h"

class Menu
{

public:

	static constexpr int ESC = 27;
	static constexpr char RESUME_GAME = '4';
	static constexpr char INSTRUCTIONS = '8';
	static constexpr char EXIT = '9';
	static constexpr char COMPUTER_VS_COMPUTER = '3';
	static constexpr char HUMAN_VS_COMPUTER = '2';
	static constexpr char HUMAN_VS_HUMAN = '1';

	void MainMenu(); //This function is opening up the menu of the game.

	void PrintMenu() const;//This function prints the menu.

	void PrintInstructions() const; //This function prints the instractions.

	void PrintPausedMenu() const; //This function prints the menu at a paused game state.

	void PressKeyToContinue() const; //This function prints to press ESC to continue and waits for the ESC to proceed.

	void StartNewGame( Game& game); //Start a new game depends on the state of the game
	
};

