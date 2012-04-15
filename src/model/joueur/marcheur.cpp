#include "marcheur.h"

Marcheur::Marcheur(Terrain* t) : Personnage(t)
{
	this->type = MARCHEUR;
	this->tile = load_bitmap("res/tiles/marcheur.bmp", NULL);
	this->portee = 4;
}

void Marcheur::Move(int valx, int valy)
{
	bool mouv_possible = true;
	Case* temp;

	temp = t->Getcase(x+valx, y+valy);
	if(temp == NULL) mouv_possible = false;
	else if((temp->GetType() == MER && t->Getcase(x, y)->GetType() != MER)
			|| (temp->GetType() == HAUTE_MONTAGNE && t->Getcase(x, y)->GetType() != HAUTE_MONTAGNE)
			|| (temp->GetType() == MONTAGNE && t->Getcase(x, y)->GetType() != MONTAGNE))
				mouv_possible = false;

	if(mouv_possible) Personnage::Move(valx, valy);
}
