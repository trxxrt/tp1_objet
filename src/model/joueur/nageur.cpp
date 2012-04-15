#include "nageur.h"

Nageur::Nageur(Terrain* t) : Personnage(t)
{
	this->type = NAGEUR;
	this->tile = load_bitmap("res/tiles/nageur.bmp", NULL);
	this->portee = 4;
}

void Nageur::Move(int valx, int valy)
{
	bool mouv_possible = true;
	Case* temp;

	temp = t->Getcase(x+valx, y+valy);
	if(temp == NULL) mouv_possible = false;
	else if((temp->GetType() == MONTAGNE && t->Getcase(x, y)->GetType() != MONTAGNE) || (temp->GetType() == HAUTE_MONTAGNE && t->Getcase(x, y)->GetType() != HAUTE_MONTAGNE))
		mouv_possible = false;

	if(mouv_possible) Personnage::Move(valx, valy);
}
