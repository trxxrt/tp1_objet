#ifndef MONSTRE_H
#define MONSTRE_H

#include "personnage.h"


class Monstre : public Personnage
{
	public:
		Monstre(Terrain* t);
		void Move(int valx, int valy);
		void chercherJoueur(int pos_x, int pos_y);
	protected:
	private:
};

#endif // MONSTRE_H
