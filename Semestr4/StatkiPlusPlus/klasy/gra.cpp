#include "gra.h"

Gra::Gra(const std::string& A1N, const std::string& A2N, bool cmdKolor, bool stattrack)
{
    srand(time(NULL));
    std::cout << "Tworzenie rozgrywki" << std::endl;

    cleanCMD();

    Gracz1.setImie(A1N);  //= Admiral(A1N);
    Gracz2.setImie(A2N);  //= Admiral(A2N);

    std::cout << A1N << " stworz plansze" << std::endl;
    Plansza1 = boardCreate(Gracz1);
    std::cout << A2N << " stworz plansze" << std::endl;
    Plansza2 = boardCreate(Gracz2);
    kolorPlansz = cmdKolor;

    dziennik.clear();
    g1g2 = true;
    statsOut = stattrack;
    endgame = false;
    forcedQuit = false;
};

Gra::~Gra()
{
    dziennik.clear();
    kolorPlansz = false;
    statsOut = false;
    g1g2 = false;
    endgame = false;
    forcedQuit = false;
};

void Gra::cleanCMD(){ system("CLS"); };
void Gra::kolorCMD(const int& x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
};

void Gra::dodAkcjeDziennik(const std::string& tekst)
{
    dziennik.push_back(tekst);
};

void Gra::wypiszDziennik()
{
    cleanCMD();
    char useless_char{'0'};
    std::cout << "Widok: Dziennik Zdarzen\n" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    if (dziennik.empty())
    {
        int losowa = (rand() % 6);
        switch (losowa)
        {
        case 1:
            std::cout << "Jak na razie spokojnie na wodach Pacyfiku..." << std::endl;
            break;
        case 2:
            std::cout << "Wrogie statki na horyzoncie!" << std::endl;
            break;
        case 3:
            std::cout << "Kiepski moment na rejs wycieczkowy..." << std::endl;
            break;
        case 4:
            std::cout << "Pogoda na dzis - zachmurzenie calkowite, moze troche popadac rakietami." << std::endl;
            break;
        case 5:
            std::cout << "Sztorm sie zbliza - slychac grzmienie dzial." << std::endl;
            break;
        case 0:
        default:
            std::cout << "Wszystkie znaki na niebie i wodzie wskazuja, ze jestesmy pod ostrzalem." << std::endl;
            break;
        }
    }
    else
    {
        //int indeks = dziennik.size();
        for (std::string komunikat : dziennik)
        {
            //std::cout << '[' << indeks << "] - ";
            std::cout << komunikat << std::endl;
        }
    }
    std::cout << "\nAby wrocic, wpisz jeden znak\ni nacisnij Enter" << std::endl;
    std::cin >> useless_char;
};

void Gra::cleanDziennik()
{
    dziennik.clear();
};

char Gra::spotHandler(const int& punkt)
{
    char tmpC{'#'};
    switch (punkt)
    {
    case 0:
        {tmpC = '_';} //woda
        break;
    case 1:
        {tmpC = 'O';} //pudlo
        break;
    case 2:
        {tmpC = 'X';} //traf
        break;
    case 3:
        {tmpC = 'P';} //lodz_patrol
        break;
    case 4:
        {tmpC = 'N';} //niszczyciel
        break;
    case 5:
        {tmpC = '\\';} //niszczyciel_front
        break;
    case 6:
        {tmpC = 'S';} //sub
        break;
    case 7:
        {tmpC = '$';} //sub_front
        break;
    case 8:
        {tmpC = 'K';} //krazownik
        break;
    case 9:
        {tmpC = 'L';} //lotniskowiec
        break;
    default:
        {tmpC ='!';} //Blad
        break;
    }
    return tmpC;
};

char Gra::spotColor(const int& punkt)
{
    char tmpC{'#'};
    switch (punkt)
    {
    case 0:
        {tmpC = '_';
        kolorCMD(11);} //woda
        break;
    case 1:
        {tmpC = 'O';
        kolorCMD(3);} //pudlo
        break;
    case 2:
        {tmpC = 'X';
        kolorCMD(4);} //traf
        break;
    case 3:
        {tmpC = 'P';
        kolorCMD(2);} //lodz_patrol
        break;
    case 4:
        {tmpC = 'N';
        kolorCMD(2);} //niszczyciel
        break;
    case 5:
        {tmpC = '\\';
        kolorCMD(2);} //niszczyciel_front
        break;
    case 6:
        {tmpC = 'S';
        kolorCMD(2);} //sub
        break;
    case 7:
        {tmpC = '$';
        kolorCMD(2);} //sub_front
        break;
    case 8:
        {tmpC = 'K';
        kolorCMD(2);} //krazownik
        break;
    case 9:
        {tmpC = 'L';
        kolorCMD(2);} //lotniskowiec
        break;
    default:
        {tmpC ='!';
        kolorCMD(12);} //Blad
        break;
    }
    return tmpC;
};

void Gra::outRealBoard(const std::vector<std::vector<Pole>>& Pln)
{
    smart_char wiersz;
    int boardSize = 10;

    std::cout << " |0|1|2|3|4|5|6|7|8|9|" << std::endl;
    std::cout << "-+-+-+-+-+-+-+-+-+-+-+" << std::endl;

    for (int a = 0; a < boardSize;)
    {
        std::cout << wiersz << '|';
        for (int x = 0; x < boardSize;)
        {
            std::cout << spotHandler(Pln[a][x].getRealStan()) << '|';
            ++x;
        }
        std::cout << "\n-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        ++wiersz;
        ++a;
    }
};

void Gra::outOdkrytyBoard(const std::vector<std::vector<Pole>>& Pln)
{
    smart_char wiersz;
    int boardSize = 10;

    std::cout << " |0|1|2|3|4|5|6|7|8|9|" << std::endl;
    std::cout << "-+-+-+-+-+-+-+-+-+-+-+" << std::endl;

    for (int a = 0; a < boardSize;)
    {
        std::cout << wiersz << '|';
        for (int x = 0; x < boardSize;)
        {
            std::cout << spotHandler(Pln[a][x].getStan()) << '|';
            ++x;
        }
        std::cout << "\n-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        ++wiersz;
        ++a;
    }
};

void Gra::outRBKolor(const std::vector<std::vector<Pole>>& Pln)
{
    smart_char wiersz;
    int boardSize = 10;

    std::cout << " |0|1|2|3|4|5|6|7|8|9|" << std::endl;
    std::cout << "-+-+-+-+-+-+-+-+-+-+-+" << std::endl;

    for (int a = 0; a < boardSize;)
    {
        std::cout << wiersz << '|';
        for (int x = 0; x < boardSize;)
        {
            std::cout << spotColor(Pln[a][x].getRealStan());
            kolorCMD(15);
            std::cout << '|';
            ++x;
        }
        std::cout << "\n-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        ++wiersz;
        ++a;
    }
};

void Gra::outOBKolor(const std::vector<std::vector<Pole>>& Pln)
{
    smart_char wiersz;
    int boardSize = 10;

    std::cout << " |0|1|2|3|4|5|6|7|8|9|" << std::endl;
    std::cout << "-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    for (int a = 0; a < boardSize;)
    {
        std::cout << wiersz << '|';
        for (int x = 0; x < boardSize;)
        {
            std::cout << spotColor(Pln[a][x].getStan());
            kolorCMD(15);
            std::cout << '|';
            ++x;
        }
        std::cout << "\n-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        ++wiersz;
        ++a;
    }
};

void Gra::rozgrywka()
{
    do {
        ekranHotSeat();
        menuGracza();
    } while(endgame == false);
    if (g1g2)
        ekranWygranej(forcedQuit, Gracz2.getImie());
    else
        ekranWygranej(forcedQuit, Gracz1.getImie());
};

void Gra::menuGracza()
{
    std::string wybor {""};
    std::regex forceQuit("EXIT");
    if (g1g2)
    {
        do {
            cleanCMD();
            std::cout << Gracz1.getImie() << std::endl;
            std::cout << "\n\n----------Co zrobic?----------" << std::endl;
            std::cout << "[1] - Atakuj przeciwnika" << std::endl;
            std::cout << "[2] - Zobacz dziennik zdarzen" << std::endl;
            std::cout << "[3] - Zobacz swoja plansze" << std::endl;
            std::cout << "[EXIT] - Wyjscie z gry" << std::endl;
            std::cin >> wybor;
            //switch nie obsluguje string
            if (wybor == "1")
            {
                cleanCMD();
                std::cout << "Widok: Plansza przeciwnika\n" << std::endl;

                if (kolorPlansz)
                    outOBKolor(Plansza2);
                else
                    outOdkrytyBoard(Plansza2);

                std::string odp = menuAtaku();
                if (odp == "ww")
                    wybor = "Tura_trwa";
                else
                {
                    int indeksA = dekoduj(odp[0]);
                    int indeksB = dekoduj(odp[1]);
                    odp[1] = dekodchar(odp[1]);
                    int punkt = Plansza2[indeksA][indeksB].getRealStan();
                    std::string akcja = Gracz1.getImie();
                    switch (punkt)
                    {
                    default:
                    case 1: //pudlo
                    case 2: //traf
                        wybor = "Tura_trwa";
                        break;
                    case 0:
                        {
                            akcja.append(" atakuje pole ");
                            akcja.append(odp);
                            dodAkcjeDziennik(akcja);
                            Plansza2[indeksA][indeksB].setStan(1);
                            Plansza2[indeksA][indeksB].setRealStan(1);
                            dodAkcjeDziennik("Pudlo!");
                            wybor = "";
                        }
                        break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        {
                            akcja.append(" atakuje pole ");
                            akcja.append(odp);
                            dodAkcjeDziennik(akcja);
                            Plansza2[indeksA][indeksB].setStan(2);
                            Plansza2[indeksA][indeksB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            Gracz1.incTraf();
                            --Gracz2;
                            if (Gracz2.getTotalHP() <= 0)
                                endgame = true;
                            wybor = "";
                        }
                        break;
                    }
                }
            }
            else if (wybor == "2")
                wypiszDziennik();
            else if (wybor == "3")
            {
                char useless {'0'};
                cleanCMD();
                std::cout << "Widok: Moja plansza\n" << std::endl;

                if (kolorPlansz)
                    outRBKolor(Plansza1);
                else
                    outRealBoard(Plansza1);

                std::cout << "Wpisz jeden znak i potwierdz Enterem" << std::endl;
                std::cin >> useless;
            }
            else if (std::regex_match (wybor, forceQuit))
                {
                    wybor = "";
                    endgame = true;
                    forcedQuit = true;
                }
            else
                wybor = "Tura_trwa";

        } while (wybor != "");
        g1g2 = false;
    }
    else
    {
        do {
            cleanCMD();
            std::cout << Gracz2.getImie() << std::endl;
            std::cout << "\n\n----------Co zrobic?----------" << std::endl;
            std::cout << "[1] - Atakuj przeciwnika" << std::endl;
            std::cout << "[2] - Zobacz dziennik zdarzen" << std::endl;
            std::cout << "[3] - Zobacz swoja plansze" << std::endl;
            std::cout << "[EXIT] - Wyjscie z gry" << std::endl;
            std::cin >> wybor;

            if (wybor == "1")
            {
                cleanCMD();
                std::cout << "Widok: Plansza przeciwnika\n" << std::endl;

                if (kolorPlansz)
                    outOBKolor(Plansza1);
                else
                    outOdkrytyBoard(Plansza1);

                std::string odp = menuAtaku();
                if (odp == "ww")
                    wybor = "Tura_trwa";
                else
                {
                    int indeksA = dekoduj(odp[0]);
                    int indeksB = dekoduj(odp[1]);
                    odp[1] = dekodchar(odp[1]);
                    int punkt = Plansza1[indeksA][indeksB].getRealStan();
                    std::string akcja = Gracz2.getImie();
                    switch (punkt)
                    {
                    default:
                    case 1:
                    case 2:
                        wybor = "Tura_trwa";
                        break;
                    case 0:
                        {
                            akcja.append(" atakuje pole ");
                            akcja.append(odp);
                            dodAkcjeDziennik(akcja);
                            Plansza1[indeksA][indeksB].setStan(1);
                            Plansza1[indeksA][indeksB].setRealStan(1);
                            dodAkcjeDziennik("Pudlo!");
                            wybor = "";
                        }
                        break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                        {
                            akcja.append(" atakuje pole ");
                            akcja.append(odp);
                            dodAkcjeDziennik(akcja);
                            Plansza1[indeksA][indeksB].setStan(2);
                            Plansza1[indeksA][indeksB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            Gracz2.incTraf();
                            --Gracz1;
                            if (Gracz1.getTotalHP() <= 0)
                                endgame = true;
                            wybor = "";
                        }
                        break;
                    }
                }
            }
            else if (wybor == "2")
                wypiszDziennik();
            else if (wybor == "3")
            {
                char useless {'0'};
                cleanCMD();
                std::cout << "Widok: Moja plansza\n" << std::endl;

                if (kolorPlansz)
                    outRBKolor(Plansza2);
                else
                    outRealBoard(Plansza2);

                std::cout << "Wpisz jeden znak i potwierdz Enterem" << std::endl;
                std::cin >> useless;
            }
            else if (std::regex_match (wybor, forceQuit))
                {
                    wybor = "";
                    endgame = true;
                    forcedQuit = true;
                }
            else
                wybor = "Tura_trwa";

        } while (wybor != "");
        g1g2 = true;
    }
};

std::string Gra::menuAtaku()
{
    std::string tekst{""};
    char wiersz {'w'};
    char kolumna {'w'};
    char wybor {'_'};
    std::cout << "\nWybierz pole do zaatakowania" << std::endl;
    std::cout << "lub [W] - powrot do menu wyzej" << std::endl;
    std::cin >> wybor;

    switch (wybor)
    {
    case 'a':
    case 'A':
        wiersz = 'a';
        break;
    case 'b':
    case 'B':
        wiersz = 'b';
        break;
    case 'c':
    case 'C':
        wiersz = 'c';
        break;
    case 'd':
    case 'D':
        wiersz = 'd';
        break;
    case 'e':
    case 'E':
        wiersz = 'e';
        break;
    case 'f':
    case 'F':
        wiersz = 'f';
        break;
    case 'g':
    case 'G':
        wiersz = 'g';
        break;
    case 'h':
    case 'H':
        {wiersz = 'h';}
        break;
    case 'i':
    case 'I':
        {wiersz = 'i';}
        break;
    case 'j':
    case 'J':
        {wiersz = 'j';}
        break;
    case 'w':
    case 'W':
    default:
        {wiersz = 'w';
        kolumna = 'w';}
        break;
    }
    if (wiersz != 'w')
    {
        std::cin >> wybor;

        switch (wybor)
        {
        case '0':
            {kolumna = 'a';}
            break;
        case '1':
            {kolumna = 'b';}
            break;
        case '2':
            {kolumna = 'c';}
            break;
        case '3':
            {kolumna = 'd';}
            break;
        case '4':
            {kolumna = 'e';}
            break;
        case '5':
            {kolumna = 'f';}
            break;
        case '6':
            {kolumna = 'g';}
            break;
        case '7':
            {kolumna = 'h';}
            break;
        case '8':
            {kolumna = 'i';}
            break;
        case '9':
            {kolumna = 'j';}
            break;
        case 'w':
        case 'W':
        default:
            {   wiersz = 'w';
                kolumna = 'w';}
            break;
        }
    }
    tekst += wiersz;
    tekst += kolumna;

    return tekst;
};

int Gra::dekoduj(const char& znak)
{
    int zwrot{0};
    switch (znak)
    {
    default:
    case 'a': zwrot = 0; break;
    case 'b': zwrot = 1; break;
    case 'c': zwrot = 2; break;
    case 'd': zwrot = 3; break;
    case 'e': zwrot = 4; break;
    case 'f': zwrot = 5; break;
    case 'g': zwrot = 6; break;
    case 'h': zwrot = 7; break;
    case 'i': zwrot = 8; break;
    case 'j': zwrot = 9; break;
    }
    return zwrot;
};

char Gra::dekodchar(const char& znak)
{
    char zwrot {'_'};
    switch (znak)
    {
    default:
    case 'a': zwrot = '0'; break;
    case 'b': zwrot = '1'; break;
    case 'c': zwrot = '2'; break;
    case 'd': zwrot = '3'; break;
    case 'e': zwrot = '4'; break;
    case 'f': zwrot = '5'; break;
    case 'g': zwrot = '6'; break;
    case 'h': zwrot = '7'; break;
    case 'i': zwrot = '8'; break;
    case 'j': zwrot = '9'; break;
    }
    return zwrot;
};

void Gra::ekranHotSeat()
{
    char nic {' '};
    cleanCMD();
    std::cout << "\tTura gracza: ";
    if (g1g2)
        std::cout << Gracz1.getImie() << std::endl;
    else
        std::cout << Gracz2.getImie() << std::endl;

    std::cout << "\nGdy bedziesz gotowy, wpisz jeden znak \ni potwierdz Enterem." << std::endl;
    std::cin >> nic;
};

void Gra::ekranWygranej(bool forcedExit, const std::string& winner)
{
    char nic {'_'};
    cleanCMD();
    if (!forcedExit)
    {
        std::cout << "Wygrywa gracz: ";
        std::cout << winner << std::endl;
        std::cout << "\nGratulacje!" << std::endl;

        if (statsOut)
        {
            std::string g1name = Gracz1.getImie();
            std::string g2name = Gracz2.getImie();
            int a1t = Gracz1.getTraf();
            int a2t = Gracz2.getTraf();
            std::thread statHandler(&Gra::zapiszStatystyki, this, std::ref(g1name), std::ref(a1t), std::ref(g2name), std::ref(a2t));
            statHandler.join();
        }
    }
    else
    {
        std::cout << "Wymuszono wyjscie z gry" << std::endl;
    }
    std::cout << "\nWpisz jeden znak i potwierdz Enterem,\naby przejsc dalej" << std::endl;
    std::cin >> nic;
};

std::vector<std::vector<Pole>> Gra::boardCreate(Admiral& cpt)
{
    std::vector<std::vector<Pole>> TmpBoard;

    Pole TmpP(0);
    std::vector<Pole> TmpV {TmpP, TmpP, TmpP, TmpP, TmpP, TmpP, TmpP, TmpP, TmpP, TmpP};
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);
    TmpBoard.push_back(TmpV);

    wstawStatek(cpt, TmpBoard, "Lotniskowiec");
    wstawStatek(cpt, TmpBoard, "Krazownik");
    wstawStatek(cpt, TmpBoard, "Lodz podwodna");
    wstawStatek(cpt, TmpBoard, "Niszczyciel");
    wstawStatek(cpt, TmpBoard, "Lodz patrolowa");

    return TmpBoard;
};

void Gra::wstawStatek(Admiral cpt, std::vector<std::vector<Pole>>& board, const std::string& statek)
{
    char wybor {'0'};
    char bufor {'0'};
    int idxA {0}, idxB {0}, idxFlot {0};
    int okretSize {1}; //Domyslnie 1 - dla Lodzi Patrolowej
    int statekID {3}; //Domyslnie 3 - dla Lodzi Patrolowej
    int wasd_bol{4};
    bool w_dol {true};
    bool w_gore {true};
    bool w_lewo {true};
    bool w_prawo {true};

    if (statek == "Lotniskowiec")
    {
        idxFlot = 4;
        okretSize = 4; //5-1
        statekID = 9;
    }
    else if (statek == "Krazownik")
    {
        idxFlot = 3;
        okretSize = 3;
        statekID = 8;
    }
    else if (statek == "Lodz podwodna")
    {
        idxFlot = 1;
        okretSize = 2;
        statekID = 6;
    }
    else if (statek == "Niszczyciel")
    {
        idxFlot = 2;
        okretSize = 2;
        statekID = 4;
    }
    else
    {
        idxFlot = 0;
        okretSize = 1;
        statekID = 3;
    }

    //wybor punktu startowego
    do {

        std::cout << "Wybierz punkt, gdzie bedzie poczatek okretu:" << statek << '\n' << std::endl;

        outRealBoard(board);

        std::cin >> bufor;

        switch (bufor)
        {
            case 'a':
            case 'A':
            case '0':
                {idxA = 0;
                wybor = '0';}
                break;
            case 'b':
            case 'B':
            case '1':
                {idxA = 1;
                wybor = '0';}
                break;
            case 'c':
            case 'C':
            case '2':
                {idxA = 2;
                wybor = '0';}
                break;
            case 'd':
            case 'D':
            case '3':
                {idxA = 3;
                wybor = '0';}
                break;
            case 'e':
            case 'E':
            case '4':
                {idxA = 4;
                wybor = '0';}
                break;
            case 'f':
            case 'F':
            case '5':
                {idxA = 5;
                wybor = '0';}
                break;
            case 'g':
            case 'G':
            case '6':
                {idxA = 6;
                wybor = '0';}
                break;
            case 'h':
            case 'H':
            case '7':
                {idxA = 7;
                wybor = '0';}
                break;
            case 'i':
            case 'I':
            case '8':
                {idxA = 8;
                wybor = '0';}
                break;
            case 'j':
            case 'J':
            case '9':
                {idxA = 9;
                wybor = '0';}
                break;
            default:
                {wybor = '_';}
                break;
        }

        std::cin >> bufor;
        switch (bufor)
        {
            case 'a':
            case 'A':
            case '0':
                {idxB = 0;}
                break;
            case 'b':
            case 'B':
            case '1':
                {idxB = 1;}
                break;
            case 'c':
            case 'C':
            case '2':
                {idxB = 2;}
                break;
            case 'd':
            case 'D':
            case '3':
                {idxB = 3;}
                break;
            case 'e':
            case 'E':
            case '4':
                {idxB = 4;}
                break;
            case 'f':
            case 'F':
            case '5':
                {idxB = 5;}
                break;
            case 'g':
            case 'G':
            case '6':
                {idxB = 6;}
                break;
            case 'h':
            case 'H':
            case '7':
                {idxB = 7;}
                break;
            case 'i':
            case 'I':
            case '8':
                {idxB = 8;}
                break;
            case 'j':
            case 'J':
            case '9':
                {idxB = 9;}
                break;
            default:
                {wybor = '_';}
                break;
        }

        if (wybor != '_')
        {
            if (board[idxA][idxB].getRealStan() == 0) //prawidlowe pole
            {
                //sprawdz lewo/prawo/dol/gora czy nie ma jakiegos innego statku

                //czy nie wychodzi poza zakres

                if (idxA + okretSize > 9) {w_dol = false; --wasd_bol; }
                else if (idxA - okretSize < 0) {w_gore = false; --wasd_bol; } //poniewaz zaden statek nie jest dluzszy niz 5 pol
                else wybor = '_';
                if (idxB + okretSize > 9) {w_prawo = false; --wasd_bol; }
                else if (idxB - okretSize < 0) {w_lewo = false; --wasd_bol; }
                else wybor = '_';

                //that's a lot of if's

                if (w_dol)
                {
                    for (int blank = 1; blank <= okretSize;)
                    {
                        if (board[idxA + blank][idxB].getRealStan() != 0)
                        {
                            w_dol = false;
                            blank = okretSize;
                            --wasd_bol;
                        }
                        ++blank;
                    }
                }
                if (w_gore)
                {
                    for (int blank = 1; blank <= okretSize;)
                    {
                        if (board[idxA - blank][idxB].getRealStan() != 0)
                        {
                            w_gore = false;
                            blank = okretSize;
                            --wasd_bol;
                        }
                        ++blank;
                    }
                }
                else wybor = '_';

                if (w_prawo)
                {
                    for (int blank = 1; blank <= okretSize;)
                    {
                        if (board[idxA][idxB + blank].getRealStan() != 0)
                        {
                            w_prawo = false;
                            blank = okretSize;
                            --wasd_bol;
                        }
                        ++blank;
                    }
                }
                if (w_lewo)
                {
                    for (int blank = 1; blank <= okretSize;)
                    {
                        if (board[idxA][idxB - blank].getRealStan() != 0)
                        {
                            w_lewo = false;
                            blank = okretSize;
                            --wasd_bol;
                        }
                        ++blank;
                    }
                }
                else wybor = '_';

                if (wasd_bol > 0)
                    {
                        wybor = '0'; //Dopiero teraz mozna stawiac statek

                        switch (statekID)
                        {
                        case 9:
                            {
                                board[idxA][idxB].setRealStan(9);
                            }
                            break;
                        case 8:
                            {
                                board[idxA][idxB].setRealStan(8);
                            }
                            break;
                        case 6:
                            {
                                board[idxA][idxB].setRealStan(7);
                            }
                            break;
                        case 4:
                            {
                                board[idxA][idxB].setRealStan(5);
                            }
                            break;
                        case 3:
                        default:
                            {
                                board[idxA][idxB].setRealStan(3);
                            }
                            break;
                        }
                    }
                else
                    wybor = '_';

            }
            else
                wybor = '_';
        }

        cleanCMD();
    } while (wybor != '0');

    cpt.ustawStatek(idxFlot, idxA, idxB);

    //rozstawienie reszty okretu
    wybor = '_';

    cleanCMD();
    outRealBoard(board);

    do {
        std::cout << "Jak skierowac statek?" << std::endl;
        if (w_gore) std::cout << "[W] - W gore" << std::endl;
        if (w_lewo) std::cout << "[A] - W lewo" << std::endl;
        if (w_dol) std::cout << "[S] - W dol" << std::endl;
        if (w_prawo) std::cout << "[D] - W prawo" << std::endl;

        std::cin >> bufor;

        switch (bufor)
        {
        case 'w':
        case 'W':
            {
                if (w_gore)
                {
                    for (int a = 1; a <= okretSize;)
                    {
                        board[idxA - a][idxB].setRealStan(statekID);
                        ++a;
                    }
                    cpt.setSail(idxFlot, 1);
                    wybor = '0';
                }
                else
                    wybor = '_';
            }
            break;
        case 'a':
        case 'A':
            {
                if (w_lewo)
                {
                    for (int a = 1; a <= okretSize;)
                    {
                        board[idxA][idxB - a].setRealStan(statekID);
                        ++a;
                    }
                    cpt.setSail(idxFlot, 2);
                    wybor = '0';
                }
                else
                    wybor = '_';
            }
            break;
        case 's':
        case 'S':
            {
                if (w_dol)
                {
                    for (int a = 1; a <= okretSize;)
                    {
                        board[idxA + a][idxB].setRealStan(statekID);
                        ++a;
                    }
                    cpt.setSail(idxFlot, 3);
                    wybor = '0';
                }
                else
                    wybor = '_';
            }
            break;
        case 'd':
        case 'D':
            {
                if (w_prawo)
                {
                    for (int a = 1; a <= okretSize;)
                    {
                        board[idxA][idxB + a].setRealStan(statekID);
                        ++a;
                    }
                    cpt.setSail(idxFlot, 4);
                    wybor = '0';
                }
                else
                    wybor = '_';
            }
            break;
        default:
            {
                std::cout << "Niepoprawna opcja" << std::endl;
                wybor = '_';
            }
            break;
        }
    } while (wybor != '0');

    cleanCMD();
};

void Gra::zapiszStatystyki(std::string& A1N, int& A1traf, std::string& A2N, int& A2traf)
{
    std::filesystem::path dir("Statystyki");

    try {
        std::filesystem::create_directories(dir);
        std::ofstream plik_out(dir / "Standard_Battle.txt");
        if (plik_out)
        {
            plik_out << "Gracz 1: " << A1N << '\n';
            plik_out << "Trafienia: " << A1traf << "\n\n";

            plik_out << "Gracz 2: " << A2N << '\n';
            plik_out << "Trafienia: " << A2traf;
        }
        else
            std::cout << "Blad zapisu" << std::endl;

        plik_out.close();

    }
    catch (std::filesystem::filesystem_error const& err)
    {
        std::cout << "Blad zapisywania statystyk: " << err.what() << std::endl;
    }
};
