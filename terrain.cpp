#include "terrain.h"

Terrain::Terrain(int x)
{
	int temp=0;

    int octaves=3;
	int frequence=5;
	float persistence=.5;
    int lissage = 5;

    int nivmer=80;
    int nivplain=160;

	this->x = x;
	this->y = x;

	Calque* clc = NULL;

	clc = new Calque(x);
	clc->generer(frequence, octaves, persistence);

	clc = clc->lisser(lissage);

	cases = (Case***)malloc(x*sizeof(Case**));

	for(int i=0; i<x; i++)
	{
		cases[i] = (Case**)malloc(x*sizeof(Case*));
		for(int j=0; j<x; j++)
		{
			temp = MONTAGNE;
			if(clc->v[i][j] < nivplain) temp = PLAINE;
			if(clc->v[i][j] < nivmer) temp = MER;
			this->cases[i][j] = new Case(i, j, temp);
		}
	}
}

Terrain::~Terrain()
{
	for (int i=0; i<this->x; i++)
		for (int j=0; j<this->y; j++)
			delete this->cases[i][j];
}

void Terrain::AfficherTerrain()
{
	for(int i=0; i<x; i++)
	{
		for(int j=0; j<y; j++)
		{
			if(cases[i][j] != NULL) printf("%d", cases[i][j]->Gettype());
		}
		printf("\n");
	}
}
