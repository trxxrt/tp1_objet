#ifndef MARCHEUR_H
#define MARCHEUR_H

#include "personnage.h"


class Marcheur : public Personnage
{
	public:
		Marcheur(Terrain* t);
		void Move(int valx, int valy);
	protected:
	private:
};

#endif // MARCHEUR_H
