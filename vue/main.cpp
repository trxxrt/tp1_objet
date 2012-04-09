#include "main.h"
#include "../misc/utilitaires.h"

using namespace std;

void Vue::initAllegro(){
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    enable_hardware_cursor();

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800,600, 0, 0) != 0)
    {
        ERREUR(allegro_error);
    }
    show_mouse(screen);

}

Vue::Vue(Terrain *t, Personnage* p)
{
    this->t=t;
    this->p=p;
    dessinerTerrain();
    bufferTerrain=create_bitmap(SCREEN_W-300,SCREEN_H);
    bufferJeu=create_bitmap(SCREEN_W,SCREEN_H);
    tailleTpix_x=t->Getx()*Case::taille_pix;
    px=py=t->Getx()/2;

}

void Vue::dessinerTerrain(){
    int color;
    int k,l;
    int tc=Case::taille_pix;
    bmpTerrain=create_bitmap(t->Getx()*tc,t->Getx()*tc);
    for(int i=0;i<t->Getx();i++){
        for(int j=0;j<t->Getx();j++){
        	if(t->Getcase(i,j)->estDecouverte())
				color = this->getColorFromType(t->Getcase(i,j)->GetType());
        	else color = makecol(50,50,50);
            for(k=i*tc;k<(i+1)*tc;k++)
                for(l=j*tc;l<(j+1)*tc;l++)
                    putpixel(bmpTerrain,k,l,color);
        }
    }
}

void Vue::updateTerrain()
{
	int color;
	int a,b;

	a = p->Getx()-4;
	if(a<0) a = 0;
	if(a+8>t->Getx()) a = t->Getx()-8;

	b = p->Gety()-4;
	if(b<0) b = 0;
	if(b+8>t->Gety()) b = t->Gety()-8;

	for(int i=a;i<a+8;i++){
        for(int j=b;j<b+8;j++){
			color = this->getColorFromType(t->Getcase(i,j)->GetType());
            for(int k=i*Case::taille_pix;k<(i+1)*Case::taille_pix;k++)
                for(int l=j*Case::taille_pix;l<(j+1)*Case::taille_pix;l++)
                    putpixel(bmpTerrain,k,l,color);
        }
	}
}

int Vue::getColorFromType(int val)
{
	if(val==MER) return makecol(0,0,255);
	if(val==PLAINE) return makecol(0,125,0);
	if(val==PLAINE_BAIE) return makecol(255,0,0);
	if(val==FORET) return makecol(0,255,0);
	if(val==RIVIERE) return makecol(0,150,255);
	if(val==MONTAGNE) return makecol(124,155,25);
	if(val==HAUTE_MONTAGNE) return makecol(200,255,50);
	return makecol(50,50,50);
}

void Vue::afficherTerrain(){
    clear_bitmap(bufferTerrain);
    int bx,by;
    bx=p->Getx()*Case::taille_pix-bufferTerrain->w/2;
    by=p->Gety()*Case::taille_pix-bufferTerrain->h/2;
    if(bx<0)bx=0;
    if(bx>=bmpTerrain->w-bufferTerrain->w) bx=bmpTerrain->w-bufferTerrain->w;
    if(by<0)by=0;
    if(by>=bmpTerrain->h-bufferTerrain->h) by=bmpTerrain->h-bufferTerrain->h;

    blit(bmpTerrain,bufferTerrain,bx,by,0,0,bufferTerrain->w,bufferTerrain->h);
}

void Vue::afficherTout(){
	updateTerrain();
    afficherTerrain();
    clear_bitmap(bufferJeu);
    blit(bufferTerrain,bufferJeu,0,0,0,0,SCREEN_W,SCREEN_H);
    BITMAP*bmp=create_bitmap(bmpTerrain->w,bmpTerrain->h);
    blit(bmpTerrain,bmp,0,0,0,0,bmpTerrain->w,bmpTerrain->h);
    stretch_blit(bmp,bufferJeu,0,0,bmpTerrain->w,bmpTerrain->h,550,30,200,200);

	for(int i=0; i<200; i++)
	{
		for(int j=0; j<30; j++)
		{
			if(p->Getenergie()/5>=i) putpixel(bufferJeu,i+550,j+350,makecol(255,0,0));
			else putpixel(bufferJeu,i+550,j+350,makecol(125,125,125));
		}
	}

	for(int i=0; i<200; i++)
	{
		for(int j=0; j<30; j++)
		{
			if(p->Gethydratation()/5>=i) putpixel(bufferJeu,i+550,j+400,makecol(0,0,255));
			else putpixel(bufferJeu,i+550,j+400,makecol(125,125,125));
		}
	}

	int x_pos = (SCREEN_W-300)/2;
	if(p->Getx()*Case::taille_pix-bufferTerrain->w/2 < 0) x_pos = p->Getx()*Case::taille_pix;
	if(p->Getx()*Case::taille_pix-bufferTerrain->w/2 >= bmpTerrain->w-bufferTerrain->w) x_pos = SCREEN_W-300 - (t->Getx() - p->Getx())*Case::taille_pix;

	int y_pos = SCREEN_H/2;
	if(p->Gety()*Case::taille_pix-bufferTerrain->h/2 < 0) y_pos = p->Gety()*Case::taille_pix;
	if(p->Gety()*Case::taille_pix-bufferTerrain->h/2 >= bmpTerrain->h-bufferTerrain->h) y_pos = SCREEN_H - (t->Gety() - p->Gety())*Case::taille_pix;

	for(int i=0; i<10; i++)
		for(int j=0; j<10; j++)
			putpixel(bufferJeu,i+x_pos,j+y_pos,makecol(255,255,255));

	if(p->Gettype() != NAGEUR)
	{
		if(p->Getgourde() == PLEINE) textout_ex(bufferJeu, font, "gourde pleine", 600, 450, makecol(255,255,255), -1);
		else textout_ex(bufferJeu, font, "gourde vide", 600, 450, makecol(255,255,255), -1);

		if(p->Getsac() == PLEINE) textout_ex(bufferJeu, font, "sac plein", 600, 470, makecol(255,255,255), -1);
		else textout_ex(bufferJeu, font, "sac vide", 600, 470, makecol(255,255,255), -1);
	}
	else
	{
		textout_ex(bufferJeu, font, "pas de gourde", 600, 450, makecol(255,255,255), -1);
		textout_ex(bufferJeu, font, "pas de sac", 600, 470, makecol(255,255,255), -1);
	}


	textout_ex(bufferJeu, font, "b : boire", 550, 500, makecol(255,255,255), -1);
	textout_ex(bufferJeu, font, "m : manger", 550, 520, makecol(255,255,255), -1);
	if(p->Gettype() != NAGEUR) textout_ex(bufferJeu, font, "g : gourde", 550, 540, makecol(255,255,255), -1);
	if(p->Gettype() != NAGEUR) textout_ex(bufferJeu, font, "s : sac", 550, 560, makecol(255,255,255), -1);

    blit(bufferJeu,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    destroy_bitmap(bmp);
}

Vue::~Vue()
{
    destroy_bitmap(bmpTerrain);
    destroy_bitmap(bufferTerrain);
    destroy_bitmap(bufferJeu);
}
