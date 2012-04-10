#ifndef TERRAIN_H
#define TERRAIN_H

#include <stdlib.h>
#include <stdio.h>
#include "../../misc/utilitaires.h"
#include "calque.h"
#include "case.h"

class Terrain
{
	private:
		int x;
		int y;
		static int nivmer;
		static int nivplaine;
		static int nivplainebaie;
		static int nivforet;
		static int nivriviere;
		static int nivmontagne;
		Case*** cases;

	public:
		/// constructors & destructors
		Terrain(int x);
		~Terrain();

		/// getters
		int Getx() { return x; }
		int Gety() { return y; }
		Case* Getcase(int x, int y) { if(x<this->x && x>=0 && y>=0 && y<this->y) return cases[x][y]; else return NULL; }

		/// setters
		void Setx(int val) { x = val; }
		void Sety(int val) { y = val; }
		void Setcase(Case* val, int x, int y) { if(x>=0 && x<this->x && y>=0 && y < this->y) cases[x][y] = val; }

		/// functions
		void AfficherTerrain();
};

#endif
