#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilitaires.h"
#include "terrain.h"
using namespace std;

int main()
{
    srand((int)time(NULL));
    initAlleg();

    int taille = 200;
    int octaves = 3;
	int frequence = 5;
	float persistence =.5;
    int lissage = 5;

    /**Un calque est tout simplement une image (matice carre) en niveau de gris (valeurs entre 0 et 255)
    Pour des explications sur la generation de terrains avec l'algo de perlin,
    consulter par exemple le site :http://khayyam.developpez.com/articles/algo/perlin/
    **/

	Calque* brut = NULL;
	Calque* lisse = NULL;

	brut = new Calque(taille);
	brut->generer(frequence, octaves, persistence);
	brut->sauvegarder((char*)"brut.txt");

	lisse = brut->lisser(lissage);
	lisse->sauvegarder((char*)"lisse.txt");

	afficherCalques(brut, lisse);

	delete brut;
	delete lisse;

	Terrain* test = new Terrain(50);
	test->AfficherTerrain();

	return 0;
}END_OF_MAIN();
