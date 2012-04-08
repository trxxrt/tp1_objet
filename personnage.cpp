#include "personnage.h"

using namespace std;

Personnage::Personnage(Terrain* t, int type)
{
	this->t = t;
	this->x = t->Getx()/2;
	this->y = t->Gety()/2;
	this->energie = PLEINE;
	this->hydratation = PLEINE;
	this->gourde = VIDE;
	this->sac = VIDE;
	this->type = type;
}

Personnage::~Personnage()
{

}

void Personnage::Setx(int val)
{
	if(val>=0 && val<t->Getx()) x = val;
	this->updateCases();
}

void Personnage::Sety(int val)
{
	if(val>=0 && val<t->Gety()) y = val;
	this->updateCases();
}

void Personnage::Setenergie(int val)
{
	if(val < VIDE) val = VIDE;
	if(val > PLEINE) val = PLEINE;
	energie = val;
}

void Personnage::Sethydratation(int val)
{
	if(val < VIDE) val = VIDE;
	if(val > PLEINE) val = PLEINE;
	hydratation = val;
}

void Personnage::Setgourde(int val)
{
	if(val < VIDE) val = VIDE;
	if(val > PLEINE) val = PLEINE;
	gourde = val;
}

void Personnage::Setsac(int val)
{
	if(val < VIDE) val = VIDE;
	if(val > PLEINE) val = PLEINE;
	sac = val;
}

bool Personnage::isAlive()
{
	if(energie > VIDE && hydratation > VIDE) return true;
	else return false;
}

void Personnage::updateCases()
{
	for(int i=-4; i<4; i++)
		for(int j=-4; j<4; j++)
			if(x+i>0 && x+i<t->Getx() && y+j>0 && y+j<t->Gety()) t->Getcase(x+i, y+j)->Setdecouverte(1);
}


void Personnage::Move(int valx, int valy)
{
	int effort = 0;

	switch(t->Getcase(x, y)->GetType())
	{
		case MER:
			effort = 3;
			break;

		case PLAINE:
		case PLAINE_BAIE:
			effort = 1;
			break;

		case FORET:
			effort = 2;
			break;

		case RIVIERE:
			effort = 1;
			break;

		case MONTAGNE:
			effort = 3;
			break;

		case HAUTE_MONTAGNE:
			effort = 5;
			break;

		default:
			effort = 5;
			break;
	}

	this->Setenergie(energie - effort);
	this->Sethydratation(hydratation - effort);

	this->Setx(x + valx);
	this->Sety(y + valy);
}

void Personnage::Boire()
{
	if(t->Getcase(x,y)->GetType() == RIVIERE)
	{
		t->Getcase(x,y)->Settype(PLAINE);
		Sethydratation(PLEINE);
	}
	while(key[KEY_B]) { rest(10); }
}

void Personnage::Manger()
{
	if(t->Getcase(x,y)->GetType() == PLAINE_BAIE)
	{
		t->Getcase(x,y)->Settype(PLAINE);
		Setenergie(PLEINE);
	}
	while(key[KEY_M]) { rest(10); }
}

void Personnage::Gourde()
{
	if(t->Getcase(x,y)->GetType() == RIVIERE)
	{
		t->Getcase(x,y)->Settype(PLAINE);
		Setgourde(PLEINE);
	}
	else if(Getgourde() != VIDE)
	{
		Sethydratation(hydratation+gourde);
		Setgourde(VIDE);
	}
	while(key[KEY_G]) { rest(10); }
}

void Personnage::Sac()
{
	if(t->Getcase(x,y)->GetType() == PLAINE_BAIE)
	{
		t->Getcase(x,y)->Settype(PLAINE);
		Setsac(PLEINE);
	}
	else if(Getsac() != VIDE)
	{
		Setenergie(energie+sac);
		Setsac(VIDE);
	}
	while(key[KEY_S]) { rest(10); }
}
