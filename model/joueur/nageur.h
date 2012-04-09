#ifndef NAGEUR_H
#define NAGEUR_H

#include "personnage.h"


class Nageur : public Personnage
{
	public:
		Nageur(Terrain* t);
		void Move(int valx, int valy);
	protected:
	private:
};

#endif // NAGEUR_H
