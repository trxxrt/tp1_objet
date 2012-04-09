#include "eclaireur.h"

Eclaireur::Eclaireur(Terrain* t) : Personnage(t)
{
	this->type = ECLAIREUR;
	this->portee = 16;
}

void Eclaireur::Move(int valx, int valy)
{
	int effort = 0;
	bool mouv_possible = true;
	Case* temp;

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

	temp = t->Getcase(x+valx, y+valy);
	if(temp == NULL) mouv_possible = false;
	else if((temp->GetType() == MER && t->Getcase(x, y)->GetType() != MER)
			|| (temp->GetType() == MONTAGNE && t->Getcase(x, y)->GetType() != MONTAGNE)
			|| (temp->GetType() == HAUTE_MONTAGNE && t->Getcase(x, y)->GetType() != HAUTE_MONTAGNE)
			|| (temp->GetType() == FORET && t->Getcase(x, y)->GetType() != FORET))
		mouv_possible = false;

	if(mouv_possible)
	{
		this->Setenergie(energie - effort);
		this->Sethydratation(hydratation - effort);

		this->Setx(x + valx);
		this->Sety(y + valy);
	}
}
