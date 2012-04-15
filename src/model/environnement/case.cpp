#include "case.h"

using namespace std;

int Case::taille_pix = 32;

BITMAP* Case::tile_mer = NULL;
BITMAP* Case::tile_plaine = NULL;
BITMAP* Case::tile_plaine_baie = NULL;
BITMAP* Case::tile_foret = NULL;
BITMAP* Case::tile_riviere = NULL;
BITMAP* Case::tile_montagne = NULL;
BITMAP* Case::tile_haute_montagne = NULL;
BITMAP* Case::tile_void = NULL;

Case::Case(int x, int y, int t)
{
	i = x;
	j = y;
	type = t;
	decouverte = 0;
	Settile(AUTRE);
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

void Case::Inittiles()
{
	Case::tile_mer = load_bitmap("res/tiles/mer.bmp", NULL);
	Case::tile_plaine = load_bitmap("res/tiles/plaine.bmp", NULL);
	Case::tile_plaine_baie = load_bitmap("res/tiles/plaine_baie.bmp", NULL);
	Case::tile_foret = load_bitmap("res/tiles/foret.bmp", NULL);
	Case::tile_riviere = load_bitmap("res/tiles/riviere.bmp", NULL);
	Case::tile_montagne = load_bitmap("res/tiles/montagne.bmp", NULL);
	Case::tile_haute_montagne = load_bitmap("res/tiles/haute_montagne.bmp", NULL);
	Case::tile_void = load_bitmap("res/tiles/void.bmp", NULL);
}

Case::~Case()
{

}
