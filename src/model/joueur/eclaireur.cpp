#include "eclaireur.h"

Eclaireur::Eclaireur(Terrain* t) : Personnage(t)
{
	this->type = ECLAIREUR;
	this->tile = load_bitmap("res/tiles/eclaireur.bmp", NULL);
	this->portee = 8;
}

void Eclaireur::Move(int valx, int valy)
{
	bool mouv_possible = true;
	Case* temp;

	temp = t->Getcase(x+valx, y+valy);
	if(temp == NULL) mouv_possible = false;
	else if((temp->GetType() == MER && t->Getcase(x, y)->GetType() != MER)
			|| (temp->GetType() == MONTAGNE && t->Getcase(x, y)->GetType() != MONTAGNE)
			|| (temp->GetType() == HAUTE_MONTAGNE && t->Getcase(x, y)->GetType() != HAUTE_MONTAGNE))
		mouv_possible = false;

	if(mouv_possible) Personnage::Move(valx, valy);
}
