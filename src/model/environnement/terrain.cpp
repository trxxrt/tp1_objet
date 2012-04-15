#include "terrain.h"

using namespace std;

int Terrain::nivmer = 100;
int Terrain::nivplaine = 120;
int Terrain::nivplainebaie = 140;
int Terrain::nivriviere = 160;
int Terrain::nivforet = 0;
int Terrain::nivmontagne = 180;


Terrain::Terrain(int x)
{
	int temp=0;

    int octaves=3;
	int frequence=5;
	float persistence=.5;
    int lissage = 5;

	this->x = x;
	this->y = x;

	Calque* clc = NULL;

	clc = new Calque(x);
	clc->generer(frequence, octaves, persistence);

	clc = clc->lisser(lissage);

	cases = new Case**[x];

	for(int i=0; i<x; i++)
	{
		cases[i] = new Case*[x];

		for(int j=0; j<x; j++)
		{
			temp = HAUTE_MONTAGNE;
			if(clc->v[i][j] < Terrain::nivmontagne) temp = MONTAGNE;
			if(clc->v[i][j] < Terrain::nivforet) temp = FORET;
			if(clc->v[i][j] < Terrain::nivriviere) temp = RIVIERE;
			if(clc->v[i][j] < Terrain::nivplainebaie) temp = PLAINE_BAIE;
			if(clc->v[i][j] < Terrain::nivplaine) temp = PLAINE;
			if(clc->v[i][j] < Terrain::nivmer) temp = MER;
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
			if(cases[i][j] != NULL) printf("%d", cases[i][j]->GetType());
		}
		printf("\n");
	}
}
