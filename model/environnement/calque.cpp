#include "calque.h"
#include "../../misc/utilitaires.h"
#include <stdio.h>

using namespace std;

Calque::Calque(int t){

    v = new int*[t];
    int i,j;
    for (i=0; i<t ; i++){
        v[i]= new int[t];
        for (j=0; j<t; j++)
            v[i][j]=0;
    }
    taille = t;
    persistance = 1;
}

Calque::Calque(int t, float p)
{

    v = new int*[t];
    int i,j;
    for (i=0; i<t ; i++){
        v[i]= new int[t];
        for (j=0; j<t; j++)
            v[i][j]=0;
    }
    taille = t;
    persistance = p;
}

Calque::Calque(int t, float p,int alea)
{

    v = new int*[t];
    int i,j;
    for (i=0; i<t ; i++){
        v[i]= new int[t];
        for (j=0; j<t; j++)
            v[i][j]=aleatoire(alea);
    }
    taille = t;
    persistance = p;
}

Calque::~Calque()
{
    int j;
    for (j=0; j<taille; j++)
        delete v[j];
    delete v;
}

void Calque::generer(int frequence,int octaves,float persistance){

    int i,j,n,f_courante;
    int a;
    float pas, sum_persistances;

    pas = (float)(taille)/frequence;
    float persistance_courante = persistance;

    Calque* random=new Calque(taille,1,256);

    Calque **mes_calques;
    mes_calques=new Calque*[octaves];
    for (i=0; i<octaves; i++){
        mes_calques[i] = new Calque(taille,persistance_courante);
        persistance_courante*=persistance;
    }

    f_courante = frequence;

    for (n=0; n<octaves; n++){
        for(i=0; i<taille; i++)
            for(j=0; j<taille; j++) {
                a = random->valeur_interpolee(i, j, f_courante);
                mes_calques[n]->v[i][j]=a;
            }
        f_courante*=frequence;
    }

    sum_persistances = 0;
    for (i=0; i<octaves; i++)
        sum_persistances+=mes_calques[i]->persistance;

    // ajout des calques successifs
    for (i=0; i<taille; i++)
        for (j=0; j<taille; j++){
            for (n=0; n<octaves; n++)
                v[i][j]+=mes_calques[n]->v[i][j]*mes_calques[n]->persistance;

            // normalisation
            v[i][j] =  v[i][j] / sum_persistances;
        }

    for (i=0; i<octaves; i++)
        delete mes_calques[i];
    delete mes_calques;
    delete random;
}

Calque* Calque::lisser(int liss){

    int x,y,k,l;
    int a,n;
    Calque *lissage;
    lissage = new Calque(taille, 0);

    for (x=0; x<taille; x++)
        for (y=0; y<taille; y++){
            a=0;
            n=0;
            for (k=x-liss; k<=x+liss; k++)
                for (l=y-liss; l<=y+liss; l++)
                    if ((k>=0) && (k<taille) && (l>=0) && (l<taille)) {
                        n++;
                        a+=v[k][l];
                    }
            lissage->v[x][y] = (float)a/n;
        }

    return lissage;
}

void Calque::sauvegarder(char* ficname){
    FILE*fp=fopen(ficname,"w");
    if(fp){
        fprintf(fp,"%d\n",taille);
        for (int x=0; x<taille; x++){
            for (int y=0; y<taille; y++){
                fprintf(fp,"%3d ",v[x][y]);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
    }
}

int Calque::valeur_interpolee(int i, int j, int frequence){

    int borne1x, borne1y, borne2x, borne2y, q;
    float pas;
    pas = (float)taille/frequence;

    q = (float)i/pas;
    borne1x = q*pas;
    borne2x = (q+1)*pas;

    if(borne2x >= taille)
        borne2x = taille-1;

    q = (float)j/pas;
    borne1y = q*pas;
    borne2y = (q+1)*pas;

    if(borne2y >= taille)
        borne2y = taille-1;

    int b00,b01,b10,b11;
    b00 = v[borne1x][borne1y];
    b01 = v[borne1x][borne2y];
    b10 = v[borne2x][borne1y];
    b11 = v[borne2x][borne2y];

    int v1 = interpolate(b00, b01, borne2y-borne1y, j-borne1y);
    int v2 = interpolate(b10, b11, borne2y-borne1y, j-borne1y);
    int fin = interpolate(v1, v2, borne2x-borne1x , i-borne1x);
    return fin;
}
