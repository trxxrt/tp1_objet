#ifndef ECLAIREUR_H
#define ECLAIREUR_H

#include "personnage.h"


class Eclaireur : public Personnage
{
	public:
		Eclaireur(Terrain* t);
		void Move(int valx, int valy);
	protected:
	private:
};

#endif // ECLAIREUR_H
