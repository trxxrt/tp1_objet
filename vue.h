#ifndef VUE_H
#define VUE_H

#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include "terrain.h"
#include "personnage.h"
#include "utilitaires.h"

class Vue
{
	public:
		BITMAP* bmpTerrain;
		BITMAP* bufferTerrain;
		BITMAP* bufferJeu;
	protected:
		Personnage* p;
		Terrain* t;
		int px;
		int py;
		int tailleTpix_x;
		int tailleTpix_y;
		static int sizeofcase_x;
		static int sizeofcase_y;

	public:
		/// constructor & destructor
		Vue(Terrain* t, Personnage* p);
		~Vue();

		/// getters
		BITMAP* GetbmpTerrain() { return bmpTerrain; }
		BITMAP* GetbufferTerrain() { return bufferTerrain; }
		BITMAP* GetbufferJeu() { return bufferJeu; }
		int Getpx() { return px; }
		int Getpy() { return py; }
		int GettailleTpix_x() { return tailleTpix_x; }
		int GettailleTpix_y() { return tailleTpix_y; }


		/// setters
		void SetbmpTerrain(BITMAP* val) { bmpTerrain = val; }
		void SetbufferTerrain(BITMAP* val) { bufferTerrain = val; }
		void SetbufferJeu(BITMAP* val) { bufferJeu = val; }
		void Setpx(int val) { px = val; }
		void Setpy(int val) { py = val; }
		void SettailleTpix_x(int val) { tailleTpix_x = val; }
		void SettailleTpix_y(int val) { tailleTpix_y = val; }


		/// public methods
		static void initAllegro();
		void afficherTout();
		void updateTerrain();

		/// protected methods
	protected:
		int makecol_from_type(int type);
		void afficherTerrain();
		void dessinerTerrain();
		int getColorFromType(int val);

};

#endif // VUE_H
