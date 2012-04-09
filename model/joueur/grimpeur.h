#ifndef GRIMPEUR_H
#define GRIMPEUR_H

#include "personnage.h"


class Grimpeur : public Personnage
{
	public:
		Grimpeur(Terrain* t);
		void Move(int valx, int valy);
	protected:
	private:
};

#endif // GRIMPEUR_H
