#ifndef CALQUE_H
#define CALQUE_H

class Calque
{
    public:
        Calque(int);
        ~Calque();
        int **v;
        int taille;

        void generer(int, int, float);
        Calque* lisser(int liss);

        void sauvegarder(char* );
    protected:
    private:
        float persistance;
        Calque(int , float );
        Calque(int , float ,int);
        int valeur_interpolee(int i, int j, int frequence);
};

#endif // CALQUE_H
