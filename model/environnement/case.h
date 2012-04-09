#ifndef CASE_H
#define CASE_H


class Case
{
	private:
		int i;
		int j;
		bool decouverte;
		int type;
	public:
		static int taille_pix;

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
};

#endif