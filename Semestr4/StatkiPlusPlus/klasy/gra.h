#ifndef GRA_H
#define GRA_H
#include "pole.h"
#include "admiral.h"
#include "smart_char.h"
#include <vector>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <regex>
#include <functional>
#include <fstream>
#include <filesystem>
#include <thread>

class Gra
{
    protected:
    std::vector<std::string> dziennik;
    std::vector<std::vector<Pole>> Plansza1;
    std::vector<std::vector<Pole>> Plansza2;
    Admiral Gracz1;
    Admiral Gracz2;
    bool kolorPlansz;
    bool g1g2;
    bool statsOut;
    bool endgame;
    bool forcedQuit;

    public:
    Gra(const std::string&, const std::string&, bool, bool);
    Gra() = delete;
    ~Gra();

    void cleanCMD();
    void kolorCMD(const int&);

    void dodAkcjeDziennik(const std::string&);
    void wypiszDziennik();
    void cleanDziennik();

    char spotHandler(const int&);
    char spotColor(const int&);
    void outRealBoard(const std::vector<std::vector<Pole>>&);
    void outOdkrytyBoard(const std::vector<std::vector<Pole>>&);
    void outRBKolor(const std::vector<std::vector<Pole>>&);
    void outOBKolor(const std::vector<std::vector<Pole>>&);

    void rozgrywka();
    void menuGracza();
    std::string menuAtaku();
    int dekoduj(const char&);
    char dekodchar(const char&);

    void ekranHotSeat();
    void ekranWygranej(bool, const std::string&);

    std::vector<std::vector<Pole>> boardCreate(Admiral&);
    void wstawStatek(Admiral, std::vector<std::vector<Pole>>&, const std::string&);

    void zapiszStatystyki(std::string&, int&, std::string&, int&);
};

#endif // GRA_H
