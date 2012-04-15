#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "../environnement/terrain.h"

#define VIDE 0
#define PLEINE 1000

#define DEFAULT 0
#define NAGEUR 1
#define MARCHEUR 2
#define ECLAIREUR 3
#define GRIMPEUR 4
#define MONSTRE 5

#define BAS 0
#define GAUCHE 1
#define DROITE 2
#define HAUT 3

#define MAX_MONSTRE 10

class Personnage
{
	protected:
		Terrain* t;
		BITMAP* tile;
		int x;
		int y;
		int portee;
		int energie;
		int hydratation;
		int gourde;
		int sac;
		int type;
		int clk;
		int direction;

	public:
		/// constructor & destructor
		Personnage(Terrain* t);
		~Personnage();

		/// getters
		int Getx() { return x; }
		int Gety() { return y; }
		int Getenergie() { return energie; }
		int Gethydratation() { return hydratation; }
		int Getgourde() { return gourde; }
		int Getsac() { return sac; }
		int Gettype() { return type; }
		int Getportee() { return portee; }
		int Getclk() { return clk; }
		int Getdirection() { return direction; }
		BITMAP* Gettile() { return tile; }
		bool isAlive();

		/// setters
		virtual void Move(int valx, int valy) = 0;
		void Setx(int val);
		void Sety(int val);
		void Setenergie(int val);
		void Sethydratation(int val);
		void Setgourde(int val);
		void Setsac(int val);
		void Setclk(int val);

		/// methodes
		void updateCases();
		void Gourde();
		void Sac();
		void Manger();
		void Boire();
};

#endif // PERSONNAGE_H
