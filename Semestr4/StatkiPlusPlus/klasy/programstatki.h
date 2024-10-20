#ifndef PROGRAMSTATKI_H
#define PROGRAMSTATKI_H
#include <iostream>
#include <windows.h>
#include "graPlusPlus.h"

class ProgramStatki
{
    private:
    bool kolorUI;
    bool statTracking;

    public:
    ProgramStatki();
    ~ProgramStatki();

    void cmdClear();
    void c_out(const std::string&);
    void c_out(const char&);
    void c_out();

    void menuGlowne();
    void menuUstawienia();
    void menuJakGrac();
    void menuTrybGry();

    void ustawieniaKolorUI();
    void ustawieniaStats();

    void wczytOpt();
    void zapisOpt();
};

#endif // PROGRAMSTATKI_H
