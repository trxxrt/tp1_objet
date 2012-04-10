#include "case.h"

using namespace std;

int Case::taille_pix=10;
BITMAP* tile_mer = load_bitmap("res/tiles/mer.bmp", NULL);
BITMAP* tile_plaine = load_bitmap("res/tiles/plaine.bmp", NULL);
BITMAP* tile_plaine_baie = load_bitmap("res/tiles/plaine_baie.bmp", NULL);
BITMAP* tile_foret = load_bitmap("res/tiles/foret.bmp", NULL);
BITMAP* tile_riviere = load_bitmap("res/tiles/riviere.bmp", NULL);
BITMAP* tile_montagne = load_bitmap("res/tiles/montagne.bmp", NULL);
BITMAP* tile_haute_montagne = load_bitmap("res/tiles/haute_montagne.bmp", NULL);

Case::Case(int x, int y, int t)
{
	i = x;
	j = y;
	type = t;
	decouverte = 0;
	Settile(type);
}

void Case::Settile(int val)
{
	switch(val)
	{
		case MER:
			tile = Case::tile_mer;
			break;

		case PLAINE:
			tile = Case::tile_plaine;
			break;

		case PLAINE_BAIE:
			tile = Case::tile_plaine_baie;
			break;

		case FORET:
			tile = Case::tile_foret;
			break;

		case RIVIERE:
			tile = Case::tile_riviere;
			break;

		case MONTAGNE:
			tile = Case::tile_montagne;
			break;

		case HAUTE_MONTAGNE:
			tile = Case::tile_haute_montagne;
			break;

		case AUTRE:
		default:
			tile = Case::tile_void;
			break;
	}

}

Case::~Case()
{

}
