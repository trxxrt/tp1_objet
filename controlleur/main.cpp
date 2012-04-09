#include "main.h"

Controller::Controller()
{
	Vue::initAllegro();
	this->ready_to_start = false;
}

Controller::~Controller()
{
	delete t;
	delete p;
	delete v;
}

void Controller::choisirJoueur()
{
	ready_to_start = true;
	type_perso = DEFAULT;

	while(type_perso == DEFAULT && !key[KEY_ESC])
	{
		if(key[KEY_M]) type_perso = MARCHEUR;
		if(key[KEY_N]) type_perso = NAGEUR;
		if(key[KEY_G]) type_perso = GRIMPEUR;
		if(key[KEY_E]) type_perso = ECLAIREUR;
	}

	initJeu();
}

void Controller::initJeu()
{
	this->t = new Terrain(200);

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
			if(p->Gettype() != NAGEUR && key[KEY_G]) p->Gourde();
			if(p->Gettype() != NAGEUR && key[KEY_S]) p->Sac();
		}

		allegro_message("End of game !");
	}
	else allegro_message("Erreur : controller::choisirjoueur() doit etre appelle avant de lancer le jeu");
}
