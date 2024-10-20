#include "programstatki.h"

ProgramStatki::ProgramStatki()
{
    kolorUI = false;
    statTracking = false;
    std::cout << "Ladowanie" << std::endl;
    wczytOpt();
};

ProgramStatki::~ProgramStatki()
{
    zapisOpt();
    kolorUI = false;
    statTracking = false;
    std::cout << "Koniec programu" << std::endl;
};

void ProgramStatki::cmdClear() { system("CLS");};
void ProgramStatki::c_out(const std::string& opis) {std::cout << opis << std::endl;};
void ProgramStatki::c_out(const char& o) {std::cout << o << std::endl;};
void ProgramStatki::c_out() {std::cout << std::endl;};

void ProgramStatki::menuGlowne()
{
    char wybor {'0'};

    do {
        cmdClear();
        c_out("Statki++\t\tv1.1\nRefactoring begins\n\t\t\tAutor: B.Nowak");

        c_out("----------------------------------------");
        c_out("[1] - Graj");
        c_out("[2] - Ustawienia");
        c_out("[3] - Jak Grac?");
        c_out("[W] - Wyjscie");
        std::cin >> wybor;

        switch (wybor)
        {
        case '1':
            menuTrybGry();
            break;
        case '2':
            menuUstawienia();
            break;
        case '3':
            menuJakGrac();
            break;
        case 'W':
        case 'w':
        case '0':
        default:
            wybor = '0';
            break;
        }

    } while (wybor != '0');
};

void ProgramStatki::menuUstawienia()
{
    char wybor{'0'};

    do {
        cmdClear();
        c_out("Menu Glowne > Ustawienia");
        c_out("\n----------------------------------------");
        c_out("[1] - Kolorowe UI podczas gry");
        c_out("[2] - Zapis statystyk po grze");
        c_out("[W] - Powrot do Menu Glownego");
        std::cin >> wybor;

        switch (wybor)
        {
        case '1':
            ustawieniaKolorUI();
            break;
        case '2':
            ustawieniaStats();
            break;
        case 'W':
        case 'w':
        case '0':
        default:
            wybor = '0';
            break;
        }

    } while (wybor != '0');
};

void ProgramStatki::menuJakGrac()
{
    char powrot {'0'};
    cmdClear();

    c_out("Menu Glowne > Jak Grac?");
    c_out("\n-------------------------------------------");
    c_out("\n> Ogolne zasady");
    c_out("Zadaniem kazdego z graczy jest zatopienie");
    c_out("wszystkich okretow przeciwnika. Podczas");
    c_out("swojej tury, gracz moze wyswietlic dziennik");
    c_out("zdarzen, sprawdzic stan swojej planszy lub");
    c_out("zaatakowac statki przeciwnika poprzez wybor");
    c_out("pojedynczego pola na planszy oponenta.");
    c_out("\n> Statki");
    c_out("Ponizej znajduja sie mozliwe okrety:");
    c_out("LLLLL\t - Lotniskowiec   | 5 HP");
    c_out("KKKK \t - Krazownik      | 4 HP");
    c_out("NN\\ \t - Nisczyciel     | 3 HP");
    c_out("SS$  \t - Lodz Podwodna  | 3 HP");
    c_out("PP   \t - Lodz Patrolowa | 2 HP");
    c_out("\n> Statki++");
    c_out("Kazdy z okretow jest teraz wyposazony w");
    c_out("umiejetnosc specjalna:");
    c_out("\n\tLotniskowiec - Nalot");
    c_out("\n\tKrazownik - Ostrzal Rakietowy");
    c_out("\n\tNiszczyciel - Salwa Torpedowa");
    c_out("\n\tLodz podwodna - Torpeda x2");
    c_out("\n\tLodz patrolowa - Zwiad");
    c_out("\n[W] - powrot do menu");
    std::cin >> powrot;
};

void ProgramStatki::menuTrybGry()
{
    char wybor {'0'};

    do {
        cmdClear();
        c_out("Menu Glowne > Tryb Gry");
        c_out("\n----------------------------------------");
        c_out("[1] - Klasyczny");
        c_out("[2] - Statki++");
        c_out("[W] - Powrot do menu glownego");
        std::cin >> wybor;

        switch (wybor)
        {
        default:
        case '0':
        case 'w':
        case 'W':
            wybor = '0';
            break;
        case '1':
            {
                std::string A1N {""}, A2N {""};

                std::cout << "\nProsze podac nazwe gracza 1" << std::endl;
                std::cin >> A1N;
                std::cout << "Prosze podac nazwe gracza 2" << std::endl;
                std::cin >> A2N;

                cmdClear();
                Gra classic(A1N, A2N, kolorUI, statTracking);
                classic.rozgrywkaLoop();
            }
            break;
        case '2':
            {
                std::string A1N {""}, A2N {""};

                std::cout << "\nProsze podac nazwe gracza 1" << std::endl;
                std::cin >> A1N;
                std::cout << "Prosze podac nazwe gracza 2" << std::endl;
                std::cin >> A2N;

                cmdClear();
                graPlusPlus modded(A1N, A2N, kolorUI, statTracking);
                modded.rozgrywka();
            }
            wybor = '0';
            break;
        }
    } while (wybor != '0');
};

void ProgramStatki::ustawieniaKolorUI()
{
    char wybor = '0';
    do {
        cmdClear();

        c_out("Menu Glowne > Ustawienia > Kolorowe UI");
        c_out("\n----------------------------------------");
        std::cout << "Kolorowe UI: ";
        if (kolorUI)
            c_out("TAK");
        else
            c_out("NIE");
        c_out("[1] - Ustaw na TAK");
        c_out("[2] - Ustaw na NIE");
        c_out("[W] - Powrot do menu ustawien");

        std::cin >> wybor;

        switch (wybor)
        {
        default:
        case '0':
        case 'w':
        case 'W':
            wybor = '0';
            break;
        case '1':
        case 'T':
        case 't':
        case 'y':
            kolorUI = true;
            break;
        case '2':
        case 'N':
        case 'n':
            kolorUI = false;
            break;
        }

    } while (wybor != '0');
};

void ProgramStatki::ustawieniaStats()
{
    char wybor = '0';
    do {
        cmdClear();

        c_out("Menu Glowne > Ustawienia > Statystyki");
        c_out("\n----------------------------------------");
        std::cout << "Zapisuj statystyki: ";
        if (statTracking)
            c_out("TAK");
        else
            c_out("NIE");
        c_out("[1] - Ustaw na TAK");
        c_out("[2] - Ustaw na NIE");
        c_out("[W] - Powrot do menu ustawien");

        std::cin >> wybor;

        switch (wybor)
        {
        default:
        case '0':
        case 'w':
        case 'W':
            wybor = '0';
            break;
        case '1':
        case 'T':
        case 't':
        case 'y':
            statTracking = true;
            break;
        case '2':
        case 'N':
        case 'n':
            statTracking = false;
            break;
        }

    } while (wybor != '0');
};

void ProgramStatki::wczytOpt()
{
    std::string bufor = "";
    std::regex klrUI ("KoloroweUI = 1");
    std::regex trkStt("Statystyki = 1");

    std::ifstream plik_in("settings.txt");
    if (plik_in)
    {
        std::getline(plik_in, bufor);
        if (std::regex_match(bufor, klrUI))
            kolorUI = true;
        else
            kolorUI = false;

        std::getline(plik_in, bufor);
        if (std::regex_match(bufor, trkStt))
            statTracking = true;
        else
            statTracking = false;
    }
    else
        std::cout << "Blad wczytywania ustawien" << std::endl;

    plik_in.close();
};

void ProgramStatki::zapisOpt()
{
    std::ofstream plik_out("settings.txt");
    if (plik_out)
    {
        plik_out << "KoloroweUI = " << kolorUI << std::endl;
        plik_out << "Statystyki = " << statTracking;
    }
    else
        std::cout << "Blad zapisywania ustawien" << std::endl;

    plik_out.close();
};
