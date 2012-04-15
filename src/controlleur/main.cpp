#include "main.h"
#if defined(linux) || defined(__linux)
  #define MY_KEY_M KEY_M
#else
  #define MY_KEY_M KEY_SEMICOLON
#endif


Controller::Controller()
{
	Vue::initAllegro();
	this->ready_to_start = false;
	Case::Inittiles();
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
		rest(50);
		if(key[MY_KEY_M]) type_perso = MARCHEUR; // fix du bug qwerty/azerty
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

	for(int i=0; i<MAX_MONSTRE; i++)
		this->monstres[i] = NULL;

	this->v = new Vue(t, p);
}

void Controller::start()
{
	int clk = 1;

	if(ready_to_start)
	{
		for(int i=0; i<MAX_MONSTRE; i++)
		{
			this->monstres[i] = new Monstre(t);
			v->Setmonstre(i, monstres[i]);
		}

		while(!key[KEY_ESC] && p->isAlive())
		{
			v->afficherTout();

			rest(10);

			if(key[KEY_LEFT]) p->Move(-1, 0);
			if(key[KEY_RIGHT]) p->Move(1, 0);
			if(key[KEY_UP]) p->Move(0, -1);
			if(key[KEY_DOWN]) p->Move(0, 1);
			if(key[KEY_B]) p->Boire();
			if(key[MY_KEY_M]) p->Manger();
			if(p->Gettype() != NAGEUR && p->Gettype() != GRIMPEUR && key[KEY_G]) p->Gourde();
			if(p->Gettype() != NAGEUR && p->Gettype() != ECLAIREUR && key[KEY_S]) p->Sac();

			clk++;

			for(int i=0; i<MAX_MONSTRE; i++)
			{
				if(!monstres[i]->isAlive())
				{
					this->monstres[i] = new Monstre(t);
					v->Setmonstre(i, monstres[i]);
				}
			}

			if(clk%4 == 0)
			{
				for(int i=0; i<MAX_MONSTRE; i++)
				{
					monstres[i]->chercherJoueur(p->Getx(), p->Gety());
					if(monstres[i]->Getx() == p->Getx() && monstres[i]->Gety() == p->Gety())
						p->Setenergie(0);
				}
			}
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
