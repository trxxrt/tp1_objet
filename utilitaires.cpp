#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilitaires.h"
//tirage aleatoire
unsigned char aleatoire(float a){
    return (float)rand() / RAND_MAX * a;
}
int min(int a,int b){
    if(a>b) return b;
    else return a;
}
int max(int a,int b){
    if(a>b) return a;
    else return b;
}
//interpolation
int interpolate(int y1, int y2, int n, int delta){

    // interpolation non linéaire
    if (n==0)
        return y1;
    if (n==1)
        return y2;

    float a = (float)delta/n;

    float fac1 = 3*pow(1-a, 2) - 2*pow(1-a,3);
    float fac2 = 3*pow(a, 2) - 2*pow(a, 3);

    return y1*fac1 + y2*fac2;

	//////////////////////////////////////////////

    // interpolation linéaire
    /*if (n!=0)
        return y1+delta*((float)y2-(float)y1)/(float)n;
    else
        return y1;*/
}
void initAlleg(){
   // init allegro
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800,600, 0, 0) != 0)
    {
        ERREUR(allegro_error);
    }
    show_mouse(screen);
}

void afficherCalques(Calque* s,Calque* lisse){
    BITMAP*bmp=get_bmp(s);
    BITMAP*bmpgris=get_bmp_gris(s);

    BITMAP*bmp2=get_bmp(lisse);
    BITMAP*bmp2gris=get_bmp_gris(lisse);

    //affichage allegro pour visualisation
    textprintf_ex(screen,font,125,5,makecol(255,0,0),-1,"Generation de terrains avec l'algorithme de Perlin");
    textprintf_ex(screen,font,5,5+35,makecol(255,255,255),-1,"terrain genere en niveau de gris ...");
    blit(bmpgris,screen,0,0,15,20+35,bmp->w,bmp->h);
    textprintf_ex(screen,font,5+bmp->w+100,5+35,makecol(255,255,255),-1," et apres lissage");
    blit(bmp2gris,screen,0,0,15+bmp->w+80,20+35,bmp2->w,bmp2->h);
    textprintf_ex(screen,font,5,20+bmp->h+15+35,makecol(255,255,255),-1," en se fixant 4 lignes de niveaux");
    blit(bmp,screen,0,0,15,20+bmp->h+35+35,bmp->w,bmp->h);
    blit(bmp2,screen,0,0,15+bmp->w+80,20+bmp->h+35+35,bmp2->w,bmp2->h);

    while(!key[KEY_ESC]){

    }
    destroy_bitmap(bmp);
    destroy_bitmap(bmp2);
    destroy_bitmap(bmpgris);
    destroy_bitmap(bmp2gris);
}
BITMAP* get_bmp_gris(Calque *c){
    BITMAP*bmp=create_bitmap(c->taille, c->taille);
    int i,j;
    for (i=0; i<c->taille; i++){
        for (j=0; j<c->taille; j++){
            putpixel(bmp,i,j,makecol(c->v[i][j],c->v[i][j],c->v[i][j]));
        }
    }
    return bmp;
}

BITMAP* get_bmp(Calque *c){
    BITMAP*bmp=create_bitmap(c->taille, c->taille);
    int i,j;
    for (i=0; i<c->taille; i++){
        for (j=0; j<c->taille; j++){
            if (c->v[i][j]<100) putpixel(bmp,i,j,makecol(0,0,255));
            else
                if (c->v[i][j]<160)putpixel(bmp,i,j,makecol(0,255,0));
                else if (c->v[i][j]<200)putpixel(bmp,i,j,makecol(124,155,25));
                    else putpixel(bmp,i,j,makecol(184,55,20));
        }
    }
    return bmp;
}

