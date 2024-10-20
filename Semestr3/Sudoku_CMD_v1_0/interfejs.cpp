#include "interfejs.h"
#include "gra.h"
#include <iostream>
#include <fstream>
#include <windows.h>

Interfejs::Interfejs()
{
    koloroweUI = false;
    pokazujBledy = false;
};

Interfejs::~Interfejs()
{
    std::cout << "Wyjscie z gry" << std::endl;
};

void Interfejs::czyscCMD()
{
    system("CLS");
};

void Interfejs::menuGlowne()
{
    char wybor;

    do {
        czyscCMD();
        std::cout << "Sudoku CMD v1.0" << std::endl;
        std::cout << "\n---------------------" << std::endl;
        std::cout << "[1] - Nowa plansza" << std::endl;
        std::cout << "[2] - Ustawienia" << std::endl;
        std::cout << "[0] - Wyjscie" << std::endl;

        std::cin >> wybor;

        switch (wybor)
        {
            case '1':
                //Wybor poziomu trudnosci
                submenuNowaGra();
                break;

            case '2':
                submenuPref();
                break;

            default:
            case 0:
                wybor = 0;
                break;
        }
    } while (wybor != 0);
};

void Interfejs::submenuPref()
{
    char wybor;

    do {
        czyscCMD();
        std::cout << "Menu Glowne >> Ustawienia" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "[1] - Kolorowe UI: ";
        if (koloroweUI == true)
            std::cout << "TAK" << std::endl;
        else
            std::cout << "NIE" << std::endl;
        std::cout << "[2] - Pokazywanie bledow: ";
        if (pokazujBledy == true)
            std::cout << "TAK" << std::endl;
        else
            std::cout << "NIE" << std::endl;
        std::cout << "[0] - Powrot do menu glownego" << std::endl;

        std::cin >> wybor;

        switch (wybor)
        {
            case '1':
                zmienKolorUI();
                break;

            case '2':
                zmienPokazBledow();
                break;

            default:
            case 0:
                wybor = 0;
                zapiszPref();
                std::cout << "Powrot do menu glownego" << std::endl;
                break;
        }
    } while (wybor != 0);
};

void Interfejs::submenuNowaGra()
{
    char wybor;

    do {
        czyscCMD();

        std::cout << "Menu Glowne >> Nowa Gra" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << "- Sudoku 9x9" << std::endl;
        std::cout << "[1] - Latwy" << std::endl;
        std::cout << "[2] - Sredni" << std::endl;
        std::cout << "[3] - Trudny" << std::endl;
        //std::cout << "- MegaSudoku (16x16)" << std::endl;
        //std::cout << "[M]" << std::endl;
        std::cout << "\n[0] - Powrot" << std::endl;
        std::cin >> wybor;

        switch (wybor)
        {
            case '1':
                Gra(9, 1, koloroweUI, pokazujBledy);
                break;

            case '2':
                Gra(9, 2, koloroweUI, pokazujBledy);
                break;

            case '3':
                Gra(9, 3, koloroweUI, pokazujBledy);
                break;
            /*
            case 'm':
            case 'M':
                //Mega Sudoku
                Gra(16, 1, koloroweUI, pokazujBledy);
                break;
            */
            default:
            case 0:
                wybor = 0;
            break;
        }
    } while (wybor != 0);
};

void Interfejs::zmienKolorUI()
{
    char bufor;

    czyscCMD();
    std::cout << "Menu Glowne >> Ustawienia >> Kolorowe UI" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    //std::cout << "Zwieksza czytelnosc sektorow dla rundy\ntypu MegaSudoku" << std::endl;
    std::cout << "[1] - TAK" << std::endl;
    std::cout << "[0] - NIE" << std::endl;
    std::cin >> bufor;

    switch (bufor)
    {
        case 0:
            koloroweUI = false;
            break;
        default:
            koloroweUI = true;
            break;
    }
};

void Interfejs::zmienPokazBledow()
{
    char bufor;

    std::cout << "Menu Glowne >> Ustawienia >> Pokaz Bledow" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Ta opcja dziala niezaleznie od stanu \nopcji Kolorowe UI" << std::endl;
    std::cout << "[1] - TAK" << std::endl;
    std::cout << "[0] - NIE" << std::endl;
    std::cin >> bufor;

    switch (bufor)
    {
        case '0':
            pokazujBledy = false;
            break;
        default:
            pokazujBledy = true;
            break;
    }
};

void Interfejs::zapiszPref()
{
    std::ofstream plikOut("settings.txt");
    if (plikOut)
    {
        plikOut << koloroweUI << std::endl;
        plikOut << pokazujBledy << std::endl;
    }
    else
    {
        std::cout << "Blad zapisu ustawien!" << std::endl;
    }
    plikOut.close();
};

void Interfejs::wczytPref()
{
    std::ifstream plikIn("settings.txt");
    if (plikIn)
    {
        bool bufor;
        bufor = false;

        if (plikIn >> bufor)
            koloroweUI = bufor;
        else
            std::cout << "Blad wczytywania ustawienia Kolorowe UI" << std::endl;

        if (plikIn >> bufor)
            pokazujBledy = bufor;
        else
            std::cout << "Blad wczytywania ustawienia Pokazuj Bledy" << std::endl;
    }
    else
    {
        std::cout << "Blad wczytywania ustawien!" << std::endl;
    }
    plikIn.close();
};
