//Welcome to the Tetris game made by Adi Karif (ID - 208295576) and Or Hershko (ID - 322316514).

#include "game.h"
#include <stdlib.h> 
#include <time.h>	
#include "menu.h"



void main()
{
	srand(time(NULL));

	Menu menu;

	menu.MainMenu();
}


