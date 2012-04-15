#include "grimpeur.h"

Grimpeur::Grimpeur(Terrain* t) : Personnage(t)
{
	this->type = GRIMPEUR;
	this->tile = load_bitmap("res/tiles/grimpeur.bmp", NULL);
	this->portee = 4;
}

void Grimpeur::Move(int valx, int valy)
{
	bool mouv_possible = true;
	Case* temp;

	temp = t->Getcase(x+valx, y+valy);
	if(temp == NULL) mouv_possible = false;
	else if((temp->GetType() == MER && t->Getcase(x, y)->GetType() != MER))
		mouv_possible = false;

	if(mouv_possible) Personnage::Move(valx, valy);
}
