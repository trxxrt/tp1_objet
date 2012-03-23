#ifndef TERRAIN_H
#define TERRAIN_H

#include <stdlib.h>
#include <stdio.h>
#include "utilitaires.h"
#include "Calque.h"
#include "case.h"

#define MONTAGNE 2
#define PLAINE 1
#define MER 0

class Terrain
{
	private:
		int x;
		int y;
		Case*** cases;

	public:
		/// constructors & destructors
		Terrain(int x);
		~Terrain();

		/// getters
		int Getx() { return x; }
		int Gety() { return y; }
		Case* Getcase(int x, int y) { return cases[x][y]; }

		/// setters
		void Setx(int val) { x = val; }
		void Sety(int val) { y = val; }
		void Setcase(Case* val, int x, int y) { if(x>=0 && x<this->x && y>=0 && y < this->y) cases[x][y] = val; }

		/// functions
		void AfficherTerrain();
};

#endif
