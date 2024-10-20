#ifndef GRA_H
#define GRA_H
#include "lista.h"


class Pole
{
public:
    bool gotowy;
    int targetVal;
    int wpisanyVal;

    Pole(Pole&&);
    Pole(const Pole&);
    Pole(int);
    Pole();

    int wypisz();
    bool bladCheck();
    void setZero();
    void wpisz(int);

    Pole& operator=(Pole&&);
    Pole& operator=(const Pole&);
    bool operator!=(const Pole&);

};

class Gra
{
    Lista<Lista<Pole>> Plansza;
    bool kolorUI;
    bool bledy;
public:

    //Nowa Gra
    Gra(int, int, bool, bool);
    Gra(int, int, bool);
    Gra(int, int);
    Gra(int);
    Gra();

    //Obsluga konsoli
    void czyscCMD();
    void kolorCMD(int);

    //Generowanie plansz
    void tworz_9x9();
    void ukryj_9x9(int);

    void tworz_16x16();
    void ukryj_16x16(int);

    void mieszaj(int);
    void swapRow(int);
    void swapCol(int);

    //Gra
    void wyswietl();
    void game9x9();
    int calc_zgodnosc(int);
    void endGameScreen();
};
#endif // GRA_H
