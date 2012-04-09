#ifndef UTILITAIRES_H_INCLUDED
#define UTILITAIRES_H_INCLUDED
#define ERREUR(msg) {\
   set_gfx_mode(GFX_TEXT,0,0,0,0);\
   allegro_message("erreur ligne %d, fichier %s: %s\n",__LINE__, __FILE__,msg);\
   allegro_exit();\
   exit(EXIT_FAILURE);\
}

#include <allegro.h>
#include "../model/environnement/calque.h"

unsigned char aleatoire(float );
int min(int,int);
int max(int,int);
int interpolate(int , int,  int , int );
void initAlleg();
BITMAP* get_bmp(Calque *);
BITMAP* get_bmp_gris(Calque*);
void afficherCalques(Calque*,Calque*);

#endif // UTILITAIRES_H_INCLUDED
