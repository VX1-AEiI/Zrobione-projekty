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

void graPlusPlus::menuGraczaUI()
{
    std::cout << "\n\n----------Co zrobic?----------" << std::endl;
    std::cout << "[1] - Atakuj przeciwnika" << std::endl;
    std::cout << "[2] - Zobacz dziennik zdarzen" << std::endl;
    std::cout << "[3] - Zobacz swoja plansze" << std::endl;
    std::cout << "[4] - Uzyj umiejetnosci specjalnej" << std::endl;
    std::cout << "[EXIT] - Wyjscie z gry" << std::endl;
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
            menuGraczaUI();
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

void graPlusPlus::ekranWygranej(const bool& forcedExit, const std::string& winner)
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

void graPlusPlus::specialAttackTrafAnnouncement(const int& specialTrafienia, const std::string& specialAttackName)
{
    short int x = 0;
    if (specialTrafienia > 0)
    {
        std::cout << "uzywa umiejetnosci " << specialAttackName << std::endl;
        for (; x < specialTrafienia; ++x)
            { std::cout << "Trafienie!" << std::endl; }
    }
};
