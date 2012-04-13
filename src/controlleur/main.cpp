#include "main.h"

Controller::Controller()
{
	Vue::initAllegro();
	this->ready_to_start = false;
	Case::tile_mer = load_bitmap("res/tiles/mer.bmp", NULL);
	Case::tile_plaine = load_bitmap("res/tiles/plaine.bmp", NULL);
	Case::tile_plaine_baie = load_bitmap("res/tiles/plaine_baie.bmp", NULL);
	Case::tile_foret = load_bitmap("res/tiles/foret.bmp", NULL);
	Case::tile_riviere = load_bitmap("res/tiles/riviere.bmp", NULL);
	Case::tile_montagne = load_bitmap("res/tiles/montagne.bmp", NULL);
	Case::tile_haute_montagne = load_bitmap("res/tiles/haute_montagne.bmp", NULL);
	Case::tile_void = load_bitmap("res/tiles/void.bmp", NULL);
}

Controller::~Controller()
{
	delete t;
	delete p;
	delete v;
}

void Controller::choisirJoueur()
{
	BITMAP *background = load_bitmap("res/ChoiceBackground.bmp", NULL);

	ready_to_start = true;
	type_perso = DEFAULT;

	draw_sprite(screen, background, 0, 0);

	while(type_perso == DEFAULT && !key[KEY_ESC])
	{
		rest(20);
		if(key[KEY_M]) type_perso = MARCHEUR;
		if(key[KEY_N]) type_perso = NAGEUR;
		if(key[KEY_G]) type_perso = GRIMPEUR;
		if(key[KEY_E]) type_perso = ECLAIREUR;
	}

	initJeu();
}

void Controller::initJeu()
{
	this->t = new Terrain(100);

	switch (type_perso)
	{
		case MARCHEUR:
			this->p = new Marcheur(t);
			break;

		case NAGEUR:
			this->p = new Nageur(t);
			break;

		case GRIMPEUR:
			this->p = new Grimpeur(t);
			break;

		case ECLAIREUR:
			this->p = new Eclaireur(t);
			break;

		default:
			this->p = new Marcheur(t);
			break;
	}

	this->v = new Vue(t, p);
}

void Controller::start()
{
	if(ready_to_start)
	{
		while(!key[KEY_ESC] && p->isAlive())
		{
			v->afficherTout();

			rest(10);

			if(key[KEY_LEFT]) p->Move(-1, 0);
			if(key[KEY_RIGHT]) p->Move(1, 0);
			if(key[KEY_UP]) p->Move(0, -1);
			if(key[KEY_DOWN]) p->Move(0, 1);
			if(key[KEY_B]) p->Boire();
			if(key[KEY_M]) p->Manger();
			if(p->Gettype() != NAGEUR && p->Gettype() != GRIMPEUR && key[KEY_G]) p->Gourde();
			if(p->Gettype() != NAGEUR && p->Gettype() != ECLAIREUR && key[KEY_S]) p->Sac();
		}

		allegro_message("End of game !");
	}
	else
	{
		type_perso = MARCHEUR;
		initJeu();
		start();
	}
}
