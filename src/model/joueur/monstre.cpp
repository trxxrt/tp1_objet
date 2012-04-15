#include "monstre.h"

Monstre::Monstre(Terrain* t) : Personnage(t)
{
	this->type = MONSTRE;
	this->x = rand()%t->Getx();
	this->y = rand()%t->Gety();
	this->tile = load_bitmap("res/tiles/monstre.bmp", NULL);
	this->portee = 8;
}

void Monstre::Move(int valx, int valy)
{
	if(t->Getcase(x+valx, y+valy) != NULL) Personnage::Move(valx, valy);
}

void Monstre::chercherJoueur(int pos_x, int pos_y)
{
	int mov_x = 0, mov_y = 0;

	if(pos_x > this->Getx()) mov_x = 1;
	if(pos_x < this->Getx()) mov_x = -1;
	if(pos_y > this->Gety()) mov_y = 1;
	if(pos_y < this->Gety()) mov_y = -1;

	this->Move(mov_x, mov_y);
}
