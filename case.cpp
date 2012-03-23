#include "case.h"

int Case::taille_pix=10;

Case::Case(int x, int y, int t)
{
	i = x;
	j = y;
	type = t;
}

Case::~Case()
{

}
