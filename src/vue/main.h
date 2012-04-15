#ifndef VUE_H
#define VUE_H

#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include "../model/environnement/terrain.h"
#include "../model/joueur/personnage.h"
#include "../model/joueur/monstre.h"
#include "../misc/utilitaires.h"

#define PUTPIXEL_DISPLAY 1

class Vue
{
	public:
		BITMAP* bmpTerrain;
		BITMAP* bufferTerrain;
		BITMAP* bufferJeu;
	protected:
		Personnage* p;
		Monstre* monstres[MAX_MONSTRE];
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
		void Setmonstre(int i, Monstre* val) { if(i<MAX_MONSTRE && i>=0) monstres[i] = val; }


		/// public methods
		static void initAllegro();
		void afficherTout();
		void updateTerrain();

		/// protected methods
	protected:
		void afficherPersonnage();
		void afficherGui();
		void afficherTerrain();
		void dessinerTerrain();
		void afficherMonstres(BITMAP* bmp);

};

#endif // VUE_H
