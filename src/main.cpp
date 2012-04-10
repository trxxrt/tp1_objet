#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "controlleur/main.h"

using namespace std;

int main()
{
    srand((int)time(NULL));

	Controller* game = new Controller();
	game->choisirJoueur();
	game->start();

	delete game;

	return 0;
}END_OF_MAIN();
