#ifndef CASE_H
#define CASE_H

#include <allegro.h>

#define AUTRE 7
#define HAUTE_MONTAGNE 6
#define MONTAGNE 5
#define RIVIERE 4
#define FORET 3
#define PLAINE_BAIE 2
#define PLAINE 1
#define MER 0

class Case
{
	private:
		int i;
		int j;
		bool decouverte;
		int type;
		BITMAP* tile;
	public:
		static int taille_pix;
		static BITMAP* tile_void;
		static BITMAP* tile_mer;
		static BITMAP* tile_plaine;
		static BITMAP* tile_plaine_baie;
		static BITMAP* tile_foret;
		static BITMAP* tile_riviere;
		static BITMAP* tile_montagne;
		static BITMAP* tile_haute_montagne;

	public:
		/// constructors & destructors
		Case(int x, int y, int t);
		~Case();

		/// getters
		int Geti() { return i; }
		int Getj() { return j; }
		int GetType() { return type; }
		bool estDecouverte() { return decouverte; }
		static int Gettaille_pix() { return taille_pix; }

		/// setters
		void Seti(int val) { i = val; }
		void Setj(int val) { j = val; }
		void Settype(int val) { type = val; }
		void Setdecouverte(int val) { decouverte = (bool)val; }
		void Settile(int val);

};

#endif
