#pragma once

#include "board.h"
#include <Windows.h>
#include <conio.h> 

class Computer;
class Player;

class Game {


	int stateOfGame;
	int whoPlays;
	int right_level = NO_LEVEL;
	int left_level = NO_LEVEL;

public:


	static constexpr int GAME_DIDNT_START = 1;
	static constexpr int GAME_STARTED_NO_WINNER = 2;
	static constexpr int GAME_FINISHED = 3;

	static constexpr int LEFT_BOARD = -1;
	static constexpr int RIGHT_BOARD = 1;

	static constexpr int ComputerVSComputer = 3;
	static constexpr int HumanVSComputer = 2;
	static constexpr int HumanVSHuman = 1;

	static constexpr int NO_LEVEL = 0;
	static constexpr char BEST = 'a';
	static constexpr char GOOD = 'b';
	static constexpr char NOVICE = 'c';
	static constexpr char BEST_U = 'A';
	static constexpr char GOOD_U = 'B';
	static constexpr char NOVICE_U = 'C';

	Game() { stateOfGame = GAME_DIDNT_START; } //C'tor

	void Init(Board& boardL, Board& boardR); //Initilaizes the boards depends of the current state of the game

	void StartGame(); //This function is being used to initiate a game of tetris. 

	int GetStateOfGame() const { return stateOfGame; } 

	void SetStateOfGame(int stateOfGame); // Sets the state of the game

	void SetWhoPlays(int whoplays); //Sets the players of the game

	int GetWhoPlays() const { return whoPlays; }

	bool IsGameOver(Board& winner, Board& loser); //Return the if the game is over and Prints messages accordingly

	bool IsThereNextRound(Board& board1, Board& board2, Player* player); //Return true if the game isn't over and move down the board2's current shape

	bool IsGamePaused(Board& board1, Board& board2, int keyPressed); //Return true and saves the data if the game paused

	void CreateNextRound(Board& board, Player* player);  //Initilaizes a shape or a bomb depends on the round

	void CreatePlayers(Player** player_L, Player** player_R,Board& boardL, Board& boardR);  //Initilaizes the players kind depends on the user choice

	void CheckIfHumanAndSetKey(Player* player, int keyPressed); // If the player is Human set the keyPressed

	void CheckIfComputerAndUpdateNextMove(Player* player); // If the player is a computer, update it's next move

	bool IsPlayerHuman(Player* player); // Return true if the player is human

	void ChooseLevel(); //Asks the user to choose the computer's level

	void SetLeftLevel(char level); //Sets the level of the left player

	void SetRightLevel(char level); //Sets the level of the right player

	void PrintLevelOptions() const; // Prints the level options

	void PrintAndSetLevels(const char* word); //Prints and sets the choosen level to the relevant player
};














