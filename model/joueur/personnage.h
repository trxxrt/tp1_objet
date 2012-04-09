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

class Personnage
{
	protected:
		Terrain* t;
		int x;
		int y;
		int portee;
		int energie;
		int hydratation;
		int gourde;
		int sac;
		int type;

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
		bool isAlive();

		/// setters
		virtual void Move(int valx, int valy) = 0;
		void Setx(int val);
		void Sety(int val);
		void Setenergie(int val);
		void Sethydratation(int val);
		void Setgourde(int val);
		void Setsac(int val);

		/// methodes
		void updateCases();
		void Gourde();
		void Sac();
		void Manger();
		void Boire();
};

#endif // PERSONNAGE_H
