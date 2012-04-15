#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../vue/main.h"
#include "../model/joueur/personnage.h"
#include "../model/joueur/nageur.h"
#include "../model/joueur/marcheur.h"
#include "../model/joueur/grimpeur.h"
#include "../model/joueur/eclaireur.h"
#include "../model/joueur/monstre.h"
#include "../model/environnement/terrain.h"

class Controller
{
	private:
		Vue* v;
		Terrain* t;
		Personnage* p;
		Monstre* monstres[MAX_MONSTRE];
		int type_perso;
		bool ready_to_start;

	public:
		/// constructeur & destructeur
		Controller();
		~Controller();

		/// getters
		Vue* Getv() { return v; }
		Terrain* Gett() { return t; }
		Personnage* Getp() { return p; }
		int Gettype_perso() { return type_perso; }

		/// setters
		void Setv(Vue* val) { v = val; }
		void Sett(Terrain* val) { t = val; }
		void Setp(Personnage* val) { p = val; }
		void Settype_perso(int val) { type_perso = val; }

		/// methods publiques
		void start();
		void choisirJoueur();

		/// methods privées
	private:
		void initJeu();
};

#endif // CONTROLLER_H
