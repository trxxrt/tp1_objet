#include "main.h"
#include "../misc/utilitaires.h"

using namespace std;

void Vue::initAllegro(){
    allegro_init();

    install_keyboard();
   	const char *override_data = "[system]\n"
	"keyboard=FR";
	override_config_data(override_data, ustrsize(override_data));

    install_mouse();
    enable_hardware_cursor();

    set_color_depth(32);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800,600, 0, 0) != 0)
        ERREUR(allegro_error);

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
    int tc=Case::taille_pix;
    bmpTerrain=create_bitmap(t->Getx()*tc,t->Getx()*tc);
    for(int i=0;i<t->Getx();i++){
        for(int j=0;j<t->Getx();j++){
        	if(t->Getcase(i,j)->estDecouverte())
				t->Getcase(i,j)->Settile(t->Getcase(i,j)->GetType());
        	else t->Getcase(i,j)->Settile(AUTRE);
			draw_sprite(bmpTerrain, t->Getcase(i,j)->Gettile(), i*Case::taille_pix, j*Case::taille_pix);
        }
    }
}

void Vue::updateTerrain()
{
	int a,b;

	a = p->Getx()-(p->Getportee()/2);
	if(a<0) a = 0;
	if((a + p->Getportee()) > t->Getx()) a = t->Getx() - p->Getportee();

	b = p->Gety() - p->Getportee()/2;
	if(b<0) b = 0;
	if(b + p->Getportee() > t->Gety()) b = t->Gety() - p->Getportee();

	for(int i=a;i<a+p->Getportee();i++){
        for(int j=b;j<b+p->Getportee();j++){
			t->Getcase(i,j)->Settile(t->Getcase(i,j)->GetType());
            draw_sprite(bmpTerrain, t->Getcase(i,j)->Gettile(), i*Case::taille_pix, j*Case::taille_pix);
        }
	}
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

    BITMAP*bmp=create_bitmap(bmpTerrain->w,bmpTerrain->h);
    draw_sprite(bmp, bmpTerrain, 0, 0);

	afficherMonstres(bmp);

    blit(bmp,bufferTerrain,bx,by,0,0,bufferTerrain->w,bufferTerrain->h);

	destroy_bitmap(bmp);
}

void Vue::afficherPersonnage()
{
	// coordonnée x du joueur
	int x_pos = (SCREEN_W-300)/2;
	if(p->Getx()*Case::taille_pix-bufferTerrain->w/2 < 0) x_pos = p->Getx()*Case::taille_pix;
	if(p->Getx()*Case::taille_pix-bufferTerrain->w/2 >= bmpTerrain->w-bufferTerrain->w) x_pos = SCREEN_W-300 - (t->Getx() - p->Getx())*Case::taille_pix;

	// coordonnée y du joueur
	int y_pos = SCREEN_H/2;
	if(p->Gety()*Case::taille_pix-bufferTerrain->h/2 < 0) y_pos = p->Gety()*Case::taille_pix;
	if(p->Gety()*Case::taille_pix-bufferTerrain->h/2 >= bmpTerrain->h-bufferTerrain->h) y_pos = SCREEN_H - (t->Gety() - p->Gety())*Case::taille_pix;

	// affichage du joueur
	masked_blit(p->Gettile(), bufferJeu, p->Getclk()*Case::taille_pix, p->Getdirection()*Case::taille_pix, x_pos, y_pos, Case::taille_pix, Case::taille_pix);
}

void Vue::afficherMonstres(BITMAP* bmp)
{
	for(int i=0; i<MAX_MONSTRE; i++)
	{
		int x_pos = monstres[i]->Getx()*Case::taille_pix;
		int y_pos = monstres[i]->Gety()*Case::taille_pix;

		if(t->Getcase(monstres[i]->Getx(), monstres[i]->Gety())->estDecouverte())
			masked_blit(monstres[i]->Gettile(),
					bmp,
					monstres[i]->Getclk()*Case::taille_pix,
					monstres[i]->Getdirection()*Case::taille_pix,
					x_pos, y_pos,
					Case::taille_pix,
					Case::taille_pix);
	}
}

void Vue::afficherGui()
{
	// barre d'énergie
	for(int i=0; i<200; i++)
	{
		for(int j=0; j<30; j++)
		{
			if(p->Getenergie()/5>=i) putpixel(bufferJeu,i+550,j+350,makecol(255,0,0));
			else putpixel(bufferJeu,i+550,j+350,makecol(125,125,125));
		}
	}

	// barre d'hydratation
	for(int i=0; i<200; i++)
	{
		for(int j=0; j<30; j++)
		{
			if(p->Gethydratation()/5>=i) putpixel(bufferJeu,i+550,j+400,makecol(0,0,255));
			else putpixel(bufferJeu,i+550,j+400,makecol(125,125,125));
		}
	}

	// affichage gui gourde et sac
	if(p->Gettype() != NAGEUR && p->Gettype() != GRIMPEUR)
	{
		if(p->Getgourde() == PLEINE) textout_ex(bufferJeu, font, "gourde pleine", 600, 450, makecol(255,255,255), -1);
		else textout_ex(bufferJeu, font, "gourde vide", 600, 450, makecol(255,255,255), -1);
	}
	else textout_ex(bufferJeu, font, "pas de gourde", 600, 450, makecol(255,255,255), -1);

	if(p->Gettype() != NAGEUR && p->Gettype() != ECLAIREUR)
	{
		if(p->Getsac() == PLEINE) textout_ex(bufferJeu, font, "sac plein", 600, 470, makecol(255,255,255), -1);
		else textout_ex(bufferJeu, font, "sac vide", 600, 470, makecol(255,255,255), -1);
	}
	else textout_ex(bufferJeu, font, "pas de sac", 600, 470, makecol(255,255,255), -1);

	textout_ex(bufferJeu, font, "b : boire", 550, 500, makecol(255,255,255), -1);
	textout_ex(bufferJeu, font, "m : manger", 550, 520, makecol(255,255,255), -1);
	if(p->Gettype() != NAGEUR) textout_ex(bufferJeu, font, "g : gourde", 550, 540, makecol(255,255,255), -1);
	if(p->Gettype() != NAGEUR) textout_ex(bufferJeu, font, "s : sac", 550, 560, makecol(255,255,255), -1);
}

void Vue::afficherTout(){

	updateTerrain();
    afficherTerrain();

    clear_bitmap(bufferJeu);
    blit(bufferTerrain,bufferJeu,0,0,0,0,SCREEN_W,SCREEN_H);

    BITMAP*bmp=create_bitmap(bmpTerrain->w,bmpTerrain->h);
    blit(bmpTerrain,bmp,0,0,0,0,bmpTerrain->w,bmpTerrain->h);
    stretch_blit(bmp,bufferJeu,0,0,bmpTerrain->w,bmpTerrain->h,550,30,200,200);

    afficherGui();
    afficherPersonnage();

    blit(bufferJeu,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    destroy_bitmap(bmp);

}

Vue::~Vue()
{
    destroy_bitmap(bmpTerrain);
    destroy_bitmap(bufferTerrain);
    destroy_bitmap(bufferJeu);
}
