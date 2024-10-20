#include "gra.h"
#include "lista.cpp"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

Pole::Pole(Pole&& inne_pole)
{
    gotowy = inne_pole.gotowy;
    targetVal = inne_pole.targetVal;
    wpisanyVal = inne_pole.wpisanyVal;

    inne_pole.gotowy = false;
    inne_pole.targetVal = 0;
    inne_pole.wpisanyVal = 0;
};

Pole::Pole(const Pole& inne_pole)
{
    gotowy = inne_pole.gotowy;
    targetVal = inne_pole.targetVal;
    wpisanyVal = inne_pole.wpisanyVal;
};

Pole::Pole()
{
    gotowy = true;
    targetVal = 0;
    wpisanyVal = 0;
};

Pole::Pole(int x)
{
    gotowy = true;
    targetVal = x;
    wpisanyVal = x;
};

int Pole::wypisz() { return wpisanyVal; };

bool Pole::bladCheck()
{
    if (wpisanyVal == targetVal)
        return false; //nie ma bledu
    else
        return true;
};

void Pole::setZero()
{
    wpisanyVal = 0;
    gotowy = false;
};

void Pole::wpisz(int x)
{
    wpisanyVal = x;
};

Pole& Pole::operator=(Pole&& inne_pole)
{
    if (*this != inne_pole)
    {
        gotowy = inne_pole.gotowy;
        targetVal = inne_pole.targetVal;
        wpisanyVal = inne_pole.wpisanyVal;

        inne_pole.gotowy = true;
        inne_pole.targetVal = 0;
        inne_pole.wpisanyVal = 0;
    }
    return *this;
};

Pole& Pole::operator=(const Pole& inne_pole)
{
    gotowy = inne_pole.gotowy;
    targetVal = inne_pole.targetVal;
    wpisanyVal = inne_pole.wpisanyVal;

    return *this;
};

bool Pole::operator!=(const Pole& inne_pole)
{
    if (targetVal == inne_pole.targetVal)
        return true;
    else
        return false;
};


Gra::Gra(int rozm, int dif, bool kolUI, bool blad)
{
    srand(time(NULL));

    int rozmiar = rozm;
    int diff = dif;
    kolorUI = kolUI;
    bledy = blad;
    czyscCMD();
    std::cout << "Tworzenie planszy, prosze czekac" << std::endl;
    switch (rozmiar)
    {
        default:
        case 9:
            tworz_9x9();
            ukryj_9x9(diff);
            game9x9();
            break;
        case 16:
            //tworz_16x16();
            //ukryj_16x16(diff);
            break;
    }
};

Gra::Gra(int rozmiar, int dif, bool kolUI)
    :Gra(rozmiar, dif, kolUI, false) {};

Gra::Gra(int rozmiar, int dif)
    :Gra(rozmiar, dif, false, false) {};

Gra::Gra(int rozmiar)
    :Gra(rozmiar, 1, false, false) {};

Gra::Gra()
    :Gra(9, 1, false, false) {};

void Gra::czyscCMD()
{
    system("CLS");
};

void Gra::kolorCMD(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
};

void Gra::tworz_9x9()
{

    Plansza.push_back(Lista<Pole> {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Plansza.push_back(Lista<Pole> {2, 3, 4, 5, 6, 7, 8, 9, 1});
    Plansza.push_back(Lista<Pole> {3, 4, 5, 6, 7, 8, 9, 1, 2});
    Plansza.push_back(Lista<Pole> {4, 5, 6, 7, 8, 9, 1, 2, 3});
    Plansza.push_back(Lista<Pole> {5, 6, 7, 8, 9, 1, 2, 3, 4});
    Plansza.push_back(Lista<Pole> {6, 7, 8, 9, 1, 2, 3, 4, 5});
    Plansza.push_back(Lista<Pole> {7, 8, 9, 1, 2, 3, 4, 5, 6});
    Plansza.push_back(Lista<Pole> {8, 9, 1, 2, 3, 4, 5, 6, 7});
    Plansza.push_back(Lista<Pole> {9, 1, 2, 3, 4, 5, 6, 7, 8});
    /*
    for (int a = 0; a < 9;)
    {
        std::cout << "[DEBUG] - " << a << ": " << Plansza[a].size() << " obiektow" << std::endl;
        ++a;
    }
    */
    mieszaj(9);
};

void Gra::ukryj_9x9(int ile)
{
    int ile_schowac = 36 + ((ile - 1) * 12);
    //std::cout << "[DEBUG] - ile_schowac = " << ile_schowac << std::endl;

    for (int x = 0; x < ile_schowac;)
    {
        //std::cout << "[DEBUG] - ile = " << ile << std::endl;
        int adres1, adres2, tempWpisVal;
        do {
            adres1 = rand() % 9;
            adres2 = rand() % 9;
            tempWpisVal = Plansza[adres1][adres2].wypisz();
            //std::cout << "[DEBUG] - tempWpisVal = " << tempWpisVal << std::endl;
            //std::cout << "[DEBUG] - Losuje" << std::endl;
        } while (tempWpisVal == 0);
        Plansza[adres1][adres2].setZero();
        ++x;
    }
    std::cout << "Plansza gotowa" << std::endl;
};

void Gra::mieszaj(int rozmiar_planszy)
{
    int ile_razy = (1000 + (rand() % 1000));
    std::cout << "Ile razy =" << ile_razy << std::endl;
    for (int x = 0; x < ile_razy;)
    {
        int rowCol = rand() % 2;
        switch (rowCol)
        {
        default:
        case 1:
            swapRow(rozmiar_planszy);
            break;
        case 0:
            swapCol(rozmiar_planszy);
            break;
        }
        ++x;
    }
    std::cout << "Losowanie planszy skonczone" << std::endl;
};

void Gra::swapRow(int przestrzen)
{
    int adres1 = rand() % przestrzen;
    int adres2;
    do {
        adres2 = rand() % przestrzen;
    } while (adres2 == adres1);

    Lista<Pole> bufor;

    bufor = Plansza[adres1];
    Plansza[adres1] = Plansza[adres2];
    Plansza[adres2] = bufor;
};

void Gra::swapCol(int przestrzen)
{
    int adres1 = rand() % przestrzen;
    int adres2;
    do {
        adres2 = rand() % przestrzen;
    } while (adres2 == adres1);

    Pole bufor;

    for(int a = 0; a < przestrzen;)
    {
        bufor = Plansza[a][adres1];
        Plansza[a][adres1] = Plansza[a][adres2];
        Plansza[a][adres2] = bufor;

        ++a;
    }
};

void Gra::wyswietl()
{
    czyscCMD();
    std::cout << "  a b c d e f g h i" << std::endl;
    kolorCMD(15);
    for (int a = 0; a < 9;)
    {
        std::cout << (a+1) << '|';
        for (int b = 0; b < 9;)
        {
            if (Plansza[a][b].bladCheck() == true)
                if (bledy == true)
                    kolorCMD(4);

            std::cout << Plansza[a][b].wypisz();
            kolorCMD(15);
            std::cout << '|';
            ++b;
        }
        std::cout << std::endl;
        //std::cout << "[DEBUG] - " << a << ": " << Plansza[a].size() << " - obiektow" << std::endl;
        ++a;
    }
};

void Gra::game9x9()
{
    int progres = calc_zgodnosc(9);
    char tmpvar;
    int row, collumn;
    do {
        wyswietl();
        std::cout << "Wybierz rzad: " << std::endl;
        std::cout << "[1]\t[2]\t[3]\t[4]\t[5]\t[6]\t[7]\t[8]\t[9]" << std::endl;
        std::cin >> tmpvar;
    switch (tmpvar)
    {
    default:
    case '1':
        row = 0;
        break;
        case '2':
        row = 1;
        break;
        case '3':
        row = 2;
        break;
        case '4':
        row = 3;
        break;
        case '5':
        row = 4;
        break;
        case '6':
        row = 5;
        break;
        case '7':
        row = 6;
        break;
        case '8':
        row = 7;
        break;
        case '9':
        row = 8;
        break;
    }
        std::cout << "Wybierz kolumne: " << std::endl;
        std::cout << "[1] - a\n[2] - b\n[3] - c\n[4] - d\n[5] - e";
        std::cout << "\n[6] - f\n[7] - g\n[8] - h\n[9] - i" << std::endl;
        std::cin >> tmpvar;
    switch (tmpvar)
    {
    default:
    case '1':
    case 'a':
    case 'A':
        collumn = 0;
        break;
    case '2':
    case 'b':
    case 'B':
        collumn = 1;
        break;
    case '3':
    case 'c':
    case 'C':
        collumn = 2;
        break;
    case '4':
    case 'd':
    case 'D':
        collumn = 3;
        break;
    case '5':
    case 'e':
    case 'E':
        collumn = 4;
        break;
    case '6':
    case 'f':
    case 'F':
        collumn = 5;
        break;
    case '7':
    case 'g':
    case 'G':
        collumn = 6;
        break;
    case '8':
    case 'h':
    case 'H':
        collumn = 7;
        break;
    case '9':
    case 'i':
    case 'I':
        collumn = 8;
        break;
    }
        std::cout << "Wstaw wartosc [0-9]" << std::endl;
        std::cin >> tmpvar;
    switch (tmpvar)
    {
        default:
        case '0':
            Plansza[row][collumn].setZero();
        break;
        case '1':
            Plansza[row][collumn].wpisz(1);
        break;
        case '2':
            Plansza[row][collumn].wpisz(2);
        break;
        case '3':
            Plansza[row][collumn].wpisz(3);
        break;
        case '4':
            Plansza[row][collumn].wpisz(4);
        break;
        case '5':
            Plansza[row][collumn].wpisz(5);
        break;
        case '6':
            Plansza[row][collumn].wpisz(6);
        break;
        case '7':
            Plansza[row][collumn].wpisz(7);
        break;
        case '8':
            Plansza[row][collumn].wpisz(8);
        break;
        case '9':
            Plansza[row][collumn].wpisz(9);
        break;
    }
    progres = calc_zgodnosc(9);
    //std::cout << "[DEBUG] - progres: " << progres << std::endl;
    } while (progres < 81);
    endGameScreen();
};

int Gra::calc_zgodnosc(int rozmiar)
{
    int ile_gotowych = 0;
    for (int a = 0; a < rozmiar;)
    {
        for (int b = 0; b < rozmiar;)
        {
            if (Plansza[a][b].bladCheck() == false)
                ++ile_gotowych;
            ++b;
        }
        ++a;
    }
    return ile_gotowych;
};

void Gra::endGameScreen()
{
    czyscCMD();
    char placeholder;
    if (kolorUI == true)
    {
        std::cout << '\t';

        kolorCMD(4);
        std::cout << "Gra";
        kolorCMD(10);
        std::cout << "tula";
        kolorCMD(1);
        std::cout << "cje!";
        kolorCMD(15);
        std::cout << "\n\nPlansza uzupelniona!" << std::endl;
    }
    else
    {
        std::cout << "\tGratulacje! \n\nPlansza uzupelniona!" << std::endl;
    }
    std::cout << "\nNacisnij dowolny przycisk, aby wrocic do menu wybierania plansz" << std::endl;
    std::cin >> placeholder;
};
