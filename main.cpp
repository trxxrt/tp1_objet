#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilitaires.h"
#include "terrain.h"
#include "vue.h"

using namespace std;

int main()
{
    srand((int)time(NULL));

	Terrain* test_terrain = new Terrain(200);
	Personnage* test_perso = new Personnage(test_terrain, DEFAULT);

	Vue::initAllegro();
	Vue* test_vue = new Vue(test_terrain, test_perso);

	while(!key[KEY_ESC] && test_perso->isAlive())
	{
		test_vue->afficherTout();

		rest(10);

		if(key[KEY_LEFT]) test_perso->Move(-1, 0);
		if(key[KEY_RIGHT]) test_perso->Move(1, 0);
		if(key[KEY_UP]) test_perso->Move(0, -1);
		if(key[KEY_DOWN]) test_perso->Move(0, 1);
		if(key[KEY_B]) test_perso->Boire();
		if(key[KEY_M]) test_perso->Manger();
		if(key[KEY_G]) test_perso->Gourde();
		if(key[KEY_S]) test_perso->Sac();
	}

	allegro_message("End of game !");

	return 0;
}END_OF_MAIN();
