#include "graPlusPlus.h"

graPlusPlus::graPlusPlus(const std::string& A1N,
    const std::string& A2N, bool kolour, bool stattrack)
    :Gra(A1N, A2N, kolour, stattrack) {};

graPlusPlus::~graPlusPlus() {};

void graPlusPlus::rozgrywka()
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

void graPlusPlus::menuGracza()
{
    int liczStatki {5};
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
            std::cout << "[4] - Uzyj umiejetnosci specjalnej" << std::endl;
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

                std::string odp = Gra::menuAtaku();
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
                            switch (punkt)
                            {
                            case 3:
                                Gracz2.ouch(0);
                                break;
                            case 4:
                            case 5:
                                Gracz2.ouch(2);
                                break;
                            case 6:
                            case 7:
                                Gracz2.ouch(1);
                                break;
                            case 8:
                                Gracz2.ouch(3);
                                break;
                            case 9:
                                Gracz2.ouch(4);
                                break;
                            }
                            akcja.append(" atakuje pole ");
                            akcja.append(odp);
                            dodAkcjeDziennik(akcja);
                            Plansza2[indeksA][indeksB].setStan(2);
                            Plansza2[indeksA][indeksB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            Gracz1.incTraf();
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
            else if (wybor == "4")
            {
                cleanCMD();
                char specSelect {'_'};
                std::string akcja = Gracz1.getImie();
                std::cout << "Widok: Menu Umiejetnosci Specjalnych" << std::endl;
                for (int x = 0; x < liczStatki; )
                {
                    std::string ok {""};
                    if (Gracz1.outSpecName(x) != ok)
                    {
                        ok = Gracz1.outSpecName(x);
                        std::cout << '[' << x << "] - " << ok << std::endl;
                    }
                    ++x;
                }

                std::cout << "[W] - Powrot do poprzedniego menu" << std::endl;
                std::cin >> specSelect;

                switch (specSelect)
                {
                default:
                case 'w':
                case 'W':
                    wybor = "Tura_trwa";
                    break;
                case '0': //Default: Patrol
                    {
                        if (Gracz1.czyMoznaUzycSpec(0))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz1.outSpecName(0));
                            dodAkcjeDziennik(akcja);
                            specialPatrol(Plansza2);
                            Gracz1.usedSpec(0);
                        }
                        wybor = "Tura_trwa";
                    }
                    break;
                case '1': //Default: Sub
                    {
                        if (Gracz1.czyMoznaUzycSpec(1))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz1.outSpecName(1));
                            dodAkcjeDziennik(akcja);
                            if (specialSub(Gracz1, Gracz2, Plansza1, Plansza2))
                            {
                                Gracz1.usedSpec(1);
                                wybor = "";
                            }
                            else
                                wybor = "Tura_trwa";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                case '2': //Default: Niszcz
                    {
                        if (Gracz1.czyMoznaUzycSpec(2))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz1.outSpecName(2));
                            dodAkcjeDziennik(akcja);

                            if (specialDestr(Gracz1, Gracz2, Plansza1, Plansza2))
                            {
                                Gracz1.usedSpec(2);
                                wybor = "";
                            }
                            else
                                wybor = "Tura_trwa";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                case '3': //Default: Cruiser
                    {
                        if (Gracz1.czyMoznaUzycSpec(3))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz1.outSpecName(3));
                            dodAkcjeDziennik(akcja);
                            specialCruis(Gracz1, Gracz2, Plansza2);
                            Gracz1.usedSpec(3);
                            wybor = "";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                case '4': //Default: Lotniskowiec
                    {
                        if (Gracz1.czyMoznaUzycSpec(4))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz1.outSpecName(4));
                            dodAkcjeDziennik(akcja);
                            specialAir(Gracz1, Gracz2, Plansza2);
                            Gracz1.usedSpec(4);
                            wybor = "";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                }
                if (Gracz2.getTotalHP() <= 0)
                {
                    endgame = true;
                    wybor = "";
                }
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
            std::cout << "[4] - Uzyj umiejetnosci specjalnej" << std::endl;
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

                std::string odp = Gra::menuAtaku();
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
                            switch (punkt)
                            {
                            case 3:
                                Gracz1.ouch(0);
                                break;
                            case 4:
                            case 5:
                                Gracz1.ouch(2);
                                break;
                            case 6:
                            case 7:
                                Gracz1.ouch(1);
                                break;
                            case 8:
                                Gracz1.ouch(3);
                                break;
                            case 9:
                                Gracz1.ouch(4);
                                break;
                            }
                            akcja.append(" atakuje pole ");
                            akcja.append(odp);
                            dodAkcjeDziennik(akcja);
                            Plansza1[indeksA][indeksB].setStan(2);
                            Plansza1[indeksA][indeksB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            Gracz2.incTraf();
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
            else if (wybor == "4")
            {
                cleanCMD();
                char specSelect {'_'};
                std::string akcja = Gracz2.getImie();
                std::cout << "Widok: Menu Umiejetnosci Specjalnych" << std::endl;
                for (int x = 0; x < liczStatki; )
                {
                    std::string ok {""};
                    if (Gracz2.outSpecName(x) != ok)
                    {
                        ok = Gracz2.outSpecName(x);
                        std::cout << '[' << x << "] - " << ok << std::endl;
                    }
                    ++x;
                }

                std::cout << "[W] - Powrot do poprzedniego menu" << std::endl;
                std::cin >> specSelect;

                switch (specSelect)
                {
                default:
                case 'w':
                case 'W':
                    wybor = "Tura_trwa";
                    break;
                case '0': //Default: Patrol
                    {
                        if (Gracz2.czyMoznaUzycSpec(0))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz2.outSpecName(0));
                            dodAkcjeDziennik(akcja);
                            specialPatrol(Plansza1);
                            Gracz2.usedSpec(0);
                        }
                        wybor = "Tura_trwa";
                    }
                    break;
                case '1': //Default: Sub
                    {
                        if (Gracz2.czyMoznaUzycSpec(1))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz2.outSpecName(1));
                            dodAkcjeDziennik(akcja);
                            if (specialSub(Gracz2, Gracz1, Plansza2, Plansza1))
                            {
                                Gracz2.usedSpec(1);
                                wybor = "";
                            }
                            else
                                wybor = "Tura_trwa";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                case '2': //Default: Niszcz
                    {
                        if (Gracz2.czyMoznaUzycSpec(2))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz2.outSpecName(2));
                            dodAkcjeDziennik(akcja);
                            if (specialDestr(Gracz2, Gracz1, Plansza2, Plansza1))
                            {

                                Gracz2.usedSpec(2);
                                wybor = "";
                            }
                            else
                                wybor = "Tura_trwa";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                case '3': //Default: Cruiser
                    {
                        if (Gracz2.czyMoznaUzycSpec(3))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz2.outSpecName(3));
                            dodAkcjeDziennik(akcja);
                            specialCruis(Gracz2, Gracz1, Plansza1);
                            Gracz2.usedSpec(3);
                            wybor = "";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                case '4': //Default: Lotniskowiec
                    {
                        if (Gracz2.czyMoznaUzycSpec(4))
                        {
                            akcja.append(" uzywa umiejetnosci ");
                            akcja.append(Gracz2.outSpecName(4));
                            dodAkcjeDziennik(akcja);
                            specialAir(Gracz2, Gracz1, Plansza1);
                            Gracz2.usedSpec(4);
                            wybor = "";
                        }
                        else
                            wybor = "Tura_trwa";
                    }
                    break;
                }
                if (Gracz1.getTotalHP() <= 0)
                {
                    endgame = true;
                    wybor = "";
                }
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

void graPlusPlus::ekranWygranej(bool forcedExit, const std::string& winner)
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
            std::thread statHandler(&graPlusPlus::zapiszStatystyki, this, std::ref(g1name), std::ref(a1t), std::ref(g2name), std::ref(a2t));
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

void graPlusPlus::specialPatrol(std::vector<std::vector<Pole>>& Pln)
{
    char wybor {'_'};
    int idxA {0}, idxB {0};
    cleanCMD();
    outOdkrytyBoard(Pln);
    do {
        std::cout << "Prosze wskazac srodek obszaru 3x3,\ngdzie ma byc przeprowadzony zwiad" << std::endl;
        std::cin >> wybor;

        switch (wybor)
        {
        case '0':
        case 'a':
        case 'A':
        case '1':
        case 'b':
        case 'B':
            {idxA = 1;
            wybor = 'O';}
            break;
        case '2':
        case 'c':
        case 'C':
            {idxA = 2;
            wybor = 'O';}
            break;
        case '3':
        case 'd':
        case 'D':
            {idxA = 3;
            wybor = 'O';}
            break;
        case '4':
        case 'e':
        case 'E':
            {idxA = 4;
            wybor = 'O';}
            break;
        case '5':
        case 'f':
        case 'F':
            {idxA = 5;
            wybor = 'O';}
            break;
        case '6':
        case 'g':
        case 'G':
            {idxA = 6;
            wybor = 'O';}
            break;
        case '7':
        case 'h':
        case 'H':
            {idxA = 7;
            wybor = 'O';}
            break;
        case '8':
        case 'i':
        case 'I':
        case '9':
        case 'j':
        case 'J':
            {idxA = 8;
            wybor = 'O';}
            break;
        default:
            wybor = '_';
            break;
        }
        if (wybor == 'O')
        {
            std::cin >> wybor;

            switch (wybor)
            {
            case '0':
            case '1':
                {idxB = 1;
                wybor = '0';}
                break;
            case '2':
                {idxB = 2;
                wybor = '0';}
                break;
            case '3':
                {idxB = 3;
                wybor = '0';}
                break;
            case '4':
                {idxB = 4;
                wybor = '0';}
                break;
            case '5':
                {idxB = 5;
                wybor = '0';}
                break;
            case '6':
                {idxB = 6;
                wybor = '0';}
                break;
            case '7':
                {idxB = 7;
                wybor = '0';}
                break;
            case '8':
            case '9':
                {idxB = 8;
                wybor = '0';}
                break;
            default:
                wybor = '_';
                break;
            }
        }


    } while (wybor != '0');

    Pln[idxA-1][idxB-1].reveal();
    Pln[idxA-1][idxB].reveal();
    Pln[idxA-1][idxB+1].reveal();
    Pln[idxA][idxB-1].reveal();
    Pln[idxA][idxB].reveal();
    Pln[idxA][idxB+1].reveal();
    Pln[idxA+1][idxB-1].reveal();
    Pln[idxA+1][idxB].reveal();
    Pln[idxA+1][idxB+1].reveal();
};

bool graPlusPlus::specialSub(Admiral& offense, Admiral& target,
                             std::vector<std::vector<Pole>>& My,
                             std::vector<std::vector<Pole>>& Oni)
{
    int idA = 0;
    int idB = 0;
    int kierunek = 0;
    short int trafienia = 0;
    int rozm = My.size();
    kierunek = offense.getSail(1);
    offense.znajdzStatek(1, idA, idB);

    switch (kierunek) {
        default:
        case 0:
            return false;
        break;
        case 1: //Atak w dol
            {
                int x = idA + 1;
                for (; x < rozm;)
                {
                    if (My[x][idB].getRealStan() > 2)
                        return false; //Nie mozna uzyc torped
                    ++x;
                }
                x = 0;

                for (; x < rozm;)
                {
                    if (trafienia < 2)
                    {
                        if (Oni[x][idB].getRealStan() > 2)
                        {
                            int idTrafStat = Oni[x][idB].getRealStan();

                            switch (idTrafStat)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB].setStan(2);
                            Oni[x][idB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            ++trafienia;
                        }
                    }
                    else
                        x = rozm;

                    ++x;
                }

                return true; //Sukces - wystrzelono torpedy
            }
        break;
        case 2: //Atak w prawo
            {
                int x = idB + 1;
                for (; x < rozm;)
                {
                    if (My[idA][x].getRealStan() > 2)
                        return false; //Nie mozna uzyc torped
                    ++x;
                }
                x = 0;

                for (; x < rozm;)
                {
                    if (trafienia < 2)
                    {
                        if (Oni[idA][x].getRealStan() > 2)
                        {
                            int idTrafStat = Oni[idA][x].getRealStan();

                            switch (idTrafStat)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA][x].setStan(2);
                            Oni[idA][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            ++trafienia;
                        }
                    }
                    else
                        x = rozm;

                    ++x;
                }

                return true;
            }
        break;
        case 3: //Atak w gore
            {
                int x = idA - 1;
                for (; x > 0;)
                {
                    if (My[x][idB].getRealStan() > 2)
                        return false; //Nie mozna uzyc torped
                    --x;
                }
                x = rozm - 1;

                for (; x > 0;)
                {
                    if (trafienia < 2)
                    {
                        if (Oni[x][idB].getRealStan() > 2)
                        {
                            int idTrafStat = Oni[x][idB].getRealStan();

                            switch (idTrafStat)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB].setStan(2);
                            Oni[x][idB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            ++trafienia;
                        }
                    }
                    else
                        x = 0;

                    --x;
                }

                return true;
            }
        break;
        case 4: //Atak w lewo
            {
                int x = idB - 1;
                for (; x > 0;)
                {
                    if (My[idA][x].getRealStan() > 2)
                        return false; //Nie mozna uzyc torped
                    --x;
                }
                x = rozm - 1;

                for (; x > 0;)
                {
                    if (trafienia < 2)
                    {
                        if (Oni[idA][x].getRealStan() > 2)
                        {
                            int idTrafStat = Oni[idA][x].getRealStan();

                            switch (idTrafStat)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA][x].setStan(2);
                            Oni[idA][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            ++trafienia;
                        }
                    }
                    else
                        x = 0;

                    --x;
                }

                return true;
            }
        break;
    }

    return false;
};
//Najdluzszy algorytm ponizej
bool graPlusPlus::specialDestr(Admiral& offense, Admiral& target,
                               std::vector<std::vector<Pole>>& My,
                               std::vector<std::vector<Pole>>& Oni)
{
    int rozmPln = My.size();
    int kierA = 0;
    int kierB = 0;
    short int trafA = 3;
    short int trafB = 3;
    bool aAtakMid = true;
    bool aAtakOff1 = true;
    bool aAtakOff2 = true;
    bool bAtakMid = true;
    bool bAtakOff1 = true;
    bool bAtakOff2 = true;
    int idA = 0;
    int idB = 0;
    int x = 0;
    int kod_pola = 0;
    int kier = offense.getSail(2);
    offense.znajdzStatek(2, idA, idB);

    switch (kier) //Ustal kierunki A i B
    {
    case 1: //w
        {
            kierA = 2;
            kierB = 4;
        }
        break;
    case 2: //a
        {
            kierA = 3;
            kierB = 1;
        }
        break;
    case 3: //s
        {
            kierA = 4;
            kierB = 2;
        }
        break;
    case 4: //d
        {
            kierA = 1;
            kierB = 3;
        }
        break;
    default:
        return false;
        break;
    }

    switch (kierA) //Zbadaj kierunek A
    {
    default:
        return false;
        break;
    case 1:
        {
            x = idA - 1;
            for (; x > 0;)
            {
                if (My[x][idB].getRealStan() > 2)
                {
                    --trafA;
                    aAtakMid = false;
                    x = 0;
                }
                --x;
            }
            x = idA - 1;

            for (; x > 0;)
            {
                if (My[x][idB+1].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff1 = false;
                    x = 0;
                }
                --x;
            }
            x = idA - 1;

            for (; x > 0;)
            {
                if (My[x][idB+2].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff2 = false;
                    x = 0;
                }
                --x;
            }
        }
        break;
    case 2:
        {
            x = idB - 1;
            for (; x > 0;)
            {
                if (My[idA][x].getRealStan() > 2)
                {
                    --trafA;
                    aAtakMid = false;
                    x = 0;
                }
                --x;
            }
            x = idB - 1;

            for (; x > 0;)
            {
                if (My[idA-1][x].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff1 = false;
                    x = 0;
                }
                --x;
            }
            x = idB - 1;

            for (; x > 0;)
            {
                if (My[idA-2][x].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff2 = false;
                    x = 0;
                }
                --x;
            }
        }
        break;
    case 3:
        {
            x = idA + 1;
            for (; x < rozmPln;)
            {
                if (My[x][idB].getRealStan() > 2)
                {
                    --trafA;
                    aAtakMid = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idA + 1;

            for (; x < rozmPln;)
            {
                if (My[x][idB-1].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff1 = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idA + 1;

            for (; x < rozmPln;)
            {
                if (My[x][idB-2].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff2 = false;
                    x = rozmPln;
                }
                ++x;
            }
        }
        break;
    case 4:
        {
            x = idB + 1;
            for (; x < rozmPln;)
            {
                if (My[idA][x].getRealStan() > 2)
                {
                    --trafA;
                    aAtakMid = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idB + 1;

            for (; x < rozmPln;)
            {
                if (My[idA+1][x].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff1 = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idB + 1;

            for (; x < rozmPln;)
            {
                if (My[idA+2][x].getRealStan() > 2)
                {
                    --trafA;
                    aAtakOff2 = false;
                    x = rozmPln;
                }
                ++x;
            }
        }
        break;
    }
    switch (kierB) //Zbadaj kierunek B
    {
    default:
        return false;
        break;
    case 1:
        {
            x = idA - 1;
            for (; x > 0;)
            {
                if (My[x][idB].getRealStan() > 2)
                {
                    --trafB;
                    bAtakMid = false;
                    x = 0;
                }
                --x;
            }
            x = idA - 1;

            for (; x > 0;)
            {
                if (My[x][idB-1].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff1 = false;
                    x = 0;
                }
                --x;
            }
            x = idA - 1;

            for (; x > 0;)
            {
                if (My[x][idB-2].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff2 = false;
                    x = 0;
                }
                --x;
            }
        }
        break;
    case 2:
        {
            x = idB - 1;
            for (; x > 0;)
            {
                if (My[idA][x].getRealStan() > 2)
                {
                    --trafB;
                    bAtakMid = false;
                    x = 0;
                }
                --x;
            }
            x = idB - 1;

            for (; x > 0;)
            {
                if (My[idA+1][x].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff1 = false;
                    x = 0;
                }
                --x;
            }
            x = idB - 1;

            for (; x > 0;)
            {
                if (My[idA+2][x].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff2 = false;
                    x = 0;
                }
                --x;
            }
        }
        break;
    case 3:
        {
            x = idA + 1;
            for (; x < rozmPln;)
            {
                if (My[x][idB].getRealStan() > 2)
                {
                    --trafB;
                    bAtakMid = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idA + 1;

            for (; x < rozmPln;)
            {
                if (My[x][idB+1].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff1 = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idA + 1;

            for (; x < rozmPln;)
            {
                if (My[x][idB+2].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff2 = false;
                    x = rozmPln;
                }
                ++x;
            }
        }
        break;
    case 4:
        {
            x = idB + 1;
            for (; x < rozmPln;)
            {
                if (My[idA][x].getRealStan() > 2)
                {
                    --trafB;
                    bAtakMid = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idB + 1;

            for (; x < rozmPln;)
            {
                if (My[idA-1][x].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff1 = false;
                    x = rozmPln;
                }
                ++x;
            }
            x = idB + 1;

            for (; x < rozmPln;)
            {
                if (My[idA-2][x].getRealStan() > 2)
                {
                    --trafB;
                    bAtakOff2 = false;
                    x = rozmPln;
                }
                ++x;
            }
        }
        break;
    }

    if ((trafA + trafB) == 0)
        return false;

    if (trafA > trafB) //uzyj A
    {
        switch (kierA)
        {
        default:
        case 0:
            return false;
            break;
        case 1:
            {
                if (aAtakMid)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[x][idB].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB].setStan(2);
                            Oni[x][idB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (aAtakOff1)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[x][idB+1].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB+1].setStan(2);
                            Oni[x][idB+1].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (aAtakOff2)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[x][idB+2].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB+2].setStan(2);
                            Oni[x][idB+2].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
            }
            break;
        case 2:
            {
                if (aAtakMid)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[idA][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA][x].setStan(2);
                            Oni[idA][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (aAtakOff1)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[idA-1][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA-1][x].setStan(2);
                            Oni[idA-1][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (aAtakOff2)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[idA-2][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA-2][x].setStan(2);
                            Oni[idA-2][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
            }
            break;
        case 3:
            {
                if (aAtakMid)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[x][idB].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB].setStan(2);
                            Oni[x][idB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (aAtakOff1)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[x][idB-1].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB-1].setStan(2);
                            Oni[x][idB-1].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (aAtakOff2)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[x][idB-2].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB-2].setStan(2);
                            Oni[x][idB-2].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
            }
            break;
        case 4:
            {
                if (aAtakMid)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[idA][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA][x].setStan(2);
                            Oni[idA][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (aAtakOff1)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[idA+1][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA+1][x].setStan(2);
                            Oni[idA+1][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (aAtakOff2)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[idA+2][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA+2][x].setStan(2);
                            Oni[idA+2][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
            }
            break;
        }

        return true;
    }
    else //uzyj B
    {
        switch (kierB)
        {
        default:
        case 0:
            return false;
            break;
        case 1:
            {
                if (bAtakMid)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[x][idB].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB].setStan(2);
                            Oni[x][idB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (bAtakOff1)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[x][idB-1].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB-1].setStan(2);
                            Oni[x][idB-1].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (bAtakOff2)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[x][idB-2].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB-2].setStan(2);
                            Oni[x][idB-2].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
            }
            break;
        case 2:
            {
                if (bAtakMid)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[idA][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA][x].setStan(2);
                            Oni[idA][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (bAtakOff1)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[idA+1][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA+1][x].setStan(2);
                            Oni[idA+1][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
                if (bAtakOff2)
                {
                    x = rozmPln - 1;
                    for (; x > 0;)
                    {
                        kod_pola = Oni[idA+2][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA+2][x].setStan(2);
                            Oni[idA+2][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = 0;
                        }
                        --x;
                    }
                }
            }
            break;
        case 3:
            {
                if (bAtakMid)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[x][idB].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB].setStan(2);
                            Oni[x][idB].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (bAtakOff1)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[x][idB+1].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB+1].setStan(2);
                            Oni[x][idB+1].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (bAtakOff2)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[x][idB+2].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[x][idB+2].setStan(2);
                            Oni[x][idB+2].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
            }
            break;
        case 4:
            {
                if (bAtakMid)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[idA][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA][x].setStan(2);
                            Oni[idA][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (bAtakOff1)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[idA-1][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA-1][x].setStan(2);
                            Oni[idA-1][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
                if (bAtakOff2)
                {
                    x = 0;
                    for (; x < rozmPln;)
                    {
                        kod_pola = Oni[idA+2][x].getRealStan();
                        if (kod_pola > 2)
                        {
                            switch (kod_pola)
                            {
                            case 3:
                                target.ouch(0);
                                break;
                            case 4:
                            case 5:
                                target.ouch(2);
                                break;
                            case 6:
                            case 7:
                                target.ouch(1);
                                break;
                            case 8:
                                target.ouch(3);
                                break;
                            case 9:
                                target.ouch(4);
                                break;
                            }

                            Oni[idA+2][x].setStan(2);
                            Oni[idA+2][x].setRealStan(2);
                            dodAkcjeDziennik("Trafienie!");
                            offense.incTraf();
                            x = rozmPln;
                        }
                        ++x;
                    }
                }
            }
            break;
        }               //Na przyszlosc: sprobowac napisac wersje 2.0 od podstaw
                        //bo az sie prosi o uzycie funkcji do tych wszystkich
        return true;    //switchy
    }

    return false;
};

void graPlusPlus::specialCruis(Admiral& offense, Admiral& tgt, std::vector<std::vector<Pole>>& Pln)
{
    std::vector<std::pair<int, int>> targets;
    std::vector<std::pair<int, int>> niewiadome;
    int pustePola = 0;
    int tmp = 0;
    int x = 0;
    int rozmPln = Pln.size();

    //Zbadaj, ile pol jeszcze zostalo do trafienia

    for (int i = 0; i < rozmPln;)
    {
        for (int j = 0; j < rozmPln;)
        {
            if (Pln[i][j].getStan() > 2)
            {
                targets.push_back({i, j});
            }
            else if (Pln[i][j].getStan() == 0)
            {
                niewiadome.push_back({i, j});
                ++pustePola;
            }
            ++j;
        }
        ++i;
    }

    if (pustePola > 4)
        pustePola = 4;

    tmp = targets.size();
    if (tmp > 4)
        tmp = 4;

    for (; x < tmp ;)
    {
        int idA = targets[x].first;
        int idB = targets[x].second;

        int okret = Pln[idA][idB].getRealStan();

        switch (okret)
        {
        case 3:
            tgt.ouch(0);
            break;
        case 4:
        case 5:
            tgt.ouch(2);
            break;
        case 6:
        case 7:
            tgt.ouch(1);
            break;
        case 8:
            tgt.ouch(3);
            break;
        case 9:
            tgt.ouch(4);
            break;
        }

        Pln[idA][idB].setStan(2);
        Pln[idA][idB].setRealStan(2);
        dodAkcjeDziennik("Trafienie!");
        offense.incTraf();
        ++x;
    }

    for (; x < pustePola;)
    {
        int wybor = 0;
        int statek = 0;
        int idA = 0;
        int idB = 0;

        do{
            wybor = rand() % niewiadome.size();

            idA = niewiadome[wybor].first;
            idB = niewiadome[wybor].second;
            statek = Pln[idA][idB].getStan();
        } while (statek != 0);

        statek = Pln[idA][idB].getRealStan();

        switch (statek)
        {
        case 0:
            {
                Pln[idA][idB].setStan(1);
                Pln[idA][idB].setRealStan(1);
                dodAkcjeDziennik("Pudlo!");
            }
            break;
        case 3:
            {
                Pln[idA][idB].setStan(2);
                Pln[idA][idB].setRealStan(2);
                tgt.ouch(0);
                dodAkcjeDziennik("Trafienie!");
                offense.incTraf();
            }
            break;
        case 4:
        case 5:
            {
                Pln[idA][idB].setStan(2);
                Pln[idA][idB].setRealStan(2);
                tgt.ouch(2);
                dodAkcjeDziennik("Trafienie!");
                offense.incTraf();
            }
            break;
        case 6:
        case 7:
            {
                Pln[idA][idB].setStan(2);
                Pln[idA][idB].setRealStan(2);
                tgt.ouch(1);
                dodAkcjeDziennik("Trafienie!");
                offense.incTraf();
            }
            break;
        case 8:
            {
                Pln[idA][idB].setStan(2);
                Pln[idA][idB].setRealStan(2);
                tgt.ouch(3);
                dodAkcjeDziennik("Trafienie!");
                offense.incTraf();
            }
            break;
        case 9:
            {
                Pln[idA][idB].setStan(2);
                Pln[idA][idB].setRealStan(2);
                tgt.ouch(4);
                dodAkcjeDziennik("Trafienie!");
                offense.incTraf();
            }
            break;
        }
        ++x;
    }
    offense.usedSpec(3);
};

void graPlusPlus::specialAir(Admiral& offense, Admiral& target, std::vector<std::vector<Pole>>& Pln)
{
    char wybor {'_'};
    int idxA = 0;
    int idxB = 0;
    int rozm = Pln.size();

    cleanCMD();
    outOdkrytyBoard(Pln);
    do {
        std::cout << "Prosze wskazac srodek obszaru \nw ksztalcie +,ktory zbombardowac" << std::endl;
        std::cin >> wybor;

        switch (wybor)
        {
        case '0':
        case 'a':
        case 'A':
            {idxA = 0;
            wybor = 'O';}
            break;
        case '1':
        case 'b':
        case 'B':
            {idxA = 1;
            wybor = 'O';}
            break;
        case '2':
        case 'c':
        case 'C':
            {idxA = 2;
            wybor = 'O';}
            break;
        case '3':
        case 'd':
        case 'D':
            {idxA = 3;
            wybor = 'O';}
            break;
        case '4':
        case 'e':
        case 'E':
            {idxA = 4;
            wybor = 'O';}
            break;
        case '5':
        case 'f':
        case 'F':
            {idxA = 5;
            wybor = 'O';}
            break;
        case '6':
        case 'g':
        case 'G':
            {idxA = 6;
            wybor = 'O';}
            break;
        case '7':
        case 'h':
        case 'H':
            {idxA = 7;
            wybor = 'O';}
            break;
        case '8':
        case 'i':
        case 'I':
            {idxA = 8;
            wybor = 'O';}
            break;
        case '9':
        case 'j':
        case 'J':
            {idxA = 9;
            wybor = 'O';}
            break;
        default:
            wybor = '_';
            break;
        }
        if (wybor == 'O')
        {
            std::cin >> wybor;

            switch (wybor)
            {
            case '0':
                {idxB = 0;
                wybor = '0';}
                break;
            case '1':
                {idxB = 1;
                wybor = '0';}
                break;
            case '2':
                {idxB = 2;
                wybor = '0';}
                break;
            case '3':
                {idxB = 3;
                wybor = '0';}
                break;
            case '4':
                {idxB = 4;
                wybor = '0';}
                break;
            case '5':
                {idxB = 5;
                wybor = '0';}
                break;
            case '6':
                {idxB = 6;
                wybor = '0';}
                break;
            case '7':
                {idxB = 7;
                wybor = '0';}
                break;
            case '8':
                {idxB = 8;
                wybor = '0';}
                break;
            case '9':
                {idxB = 9;
                wybor = '0';}
                break;
            default:
                wybor = '_';
                break;
            }
        }
    } while (wybor != '0');

    if (Pln[idxA][idxB].getRealStan() > 2)
    {
        int idTrafStat = Pln[idxA][idxB].getRealStan();

        switch (idTrafStat)
        {
        case 3:
            target.ouch(0);
            break;
        case 4:
        case 5:
            target.ouch(2);
            break;
        case 6:
        case 7:
            target.ouch(1);
            break;
        case 8:
            target.ouch(3);
            break;
        case 9:
            target.ouch(4);
            break;
        }

        Pln[idxA][idxB].setRealStan(2);
        Pln[idxA][idxB].setStan(2);
        dodAkcjeDziennik("Trafienie!");
        offense.incTraf();
    }
    else
    {
        Pln[idxA][idxB].setRealStan(1);
        Pln[idxA][idxB].setStan(1);
        dodAkcjeDziennik("Pudlo!");
    }

    if ((idxA - 1) > -1)
    {
        if (Pln[idxA - 1][idxB].getRealStan() > 2)
        {
            int idTrafStat = Pln[idxA - 1][idxB].getRealStan();

            switch (idTrafStat)
            {
            case 3:
                target.ouch(0);
                break;
            case 4:
            case 5:
                target.ouch(2);
                break;
            case 6:
            case 7:
                target.ouch(1);
                break;
            case 8:
                target.ouch(3);
                break;
            case 9:
                target.ouch(4);
                break;
            }

            Pln[idxA - 1][idxB].setRealStan(2);
            Pln[idxA - 1][idxB].setStan(2);
            dodAkcjeDziennik("Trafienie!");
            offense.incTraf();
        }
        else
        {
            Pln[idxA - 1][idxB].setRealStan(1);
            Pln[idxA - 1][idxB].setStan(1);
            dodAkcjeDziennik("Pudlo!");
        }
    }
    if ((idxA + 1) < rozm)
    {
        if (Pln[idxA + 1][idxB].getRealStan() > 2)
        {
            int idTrafStat = Pln[idxA + 1][idxB].getRealStan();

            switch (idTrafStat)
            {
            case 3:
                target.ouch(0);
                break;
            case 4:
            case 5:
                target.ouch(2);
                break;
            case 6:
            case 7:
                target.ouch(1);
                break;
            case 8:
                target.ouch(3);
                break;
            case 9:
                target.ouch(4);
                break;
            }

            Pln[idxA + 1][idxB].setRealStan(2);
            Pln[idxA + 1][idxB].setStan(2);
            dodAkcjeDziennik("Trafienie!");
            offense.incTraf();
        }
        else
        {
            Pln[idxA + 1][idxB].setRealStan(1);
            Pln[idxA + 1][idxB].setStan(1);
            dodAkcjeDziennik("Pudlo!");
        }
    }
    if ((idxB - 1) > -1)
    {
        if (Pln[idxA][idxB - 1].getRealStan() > 2)
        {
            int idTrafStat = Pln[idxA][idxB - 1].getRealStan();

            switch (idTrafStat)
            {
            case 3:
                target.ouch(0);
                break;
            case 4:
            case 5:
                target.ouch(2);
                break;
            case 6:
            case 7:
                target.ouch(1);
                break;
            case 8:
                target.ouch(3);
                break;
            case 9:
                target.ouch(4);
                break;
            }

            Pln[idxA][idxB - 1].setRealStan(2);
            Pln[idxA][idxB - 1].setStan(2);
            dodAkcjeDziennik("Trafienie!");
            offense.incTraf();
        }
        else
        {
            Pln[idxA][idxB - 1].setRealStan(1);
            Pln[idxA][idxB - 1].setStan(1);
            dodAkcjeDziennik("Pudlo!");
        }
    }
    if ((idxB + 1) < rozm)
    {
        if (Pln[idxA][idxB + 1].getRealStan() > 2)
        {
            int idTrafStat = Pln[idxA][idxB + 1].getRealStan();

            switch (idTrafStat)
            {
            case 3:
                target.ouch(0);
                break;
            case 4:
            case 5:
                target.ouch(2);
                break;
            case 6:
            case 7:
                target.ouch(1);
                break;
            case 8:
                target.ouch(3);
                break;
            case 9:
                target.ouch(4);
                break;
            }

            Pln[idxA][idxB + 1].setRealStan(2);
            Pln[idxA][idxB + 1].setStan(2);
            dodAkcjeDziennik("Trafienie!");
            offense.incTraf();
        }
        else
        {
            Pln[idxA][idxB + 1].setRealStan(1);
            Pln[idxA][idxB + 1].setStan(1);
            dodAkcjeDziennik("Pudlo!");
        }
    }
    offense.usedSpec(4);
};

void graPlusPlus::zapiszStatystyki(std::string& A1N, int& A1traf, std::string& A2N, int& A2traf)
{
    std::filesystem::path dir("Statystyki");

    try {
        std::filesystem::create_directories(dir);
        std::ofstream plik_out(dir / "Modded_Battle.txt");
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
