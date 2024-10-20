#include "submarine.h"

submarine::submarine()
    :jednostka::jednostka("Lodz podwodna", "Dwie torpedy", 3) {};

submarine::~submarine() {};

int submarine::special(const Admiral& offense, const Admiral& target,
                        const std::vector<std::vector<Pole>>& My,
                        std::vector<std::vector<Pole>>& Oni)
{
    int idA = 0;
    int idB = 0;
    int kierunek = 0;
    int licznikTraf = 0;
    kierunek = offense.getSail(1);
    offense.znajdzStatek(1, idA, idB);

    switch (kierunek) {
        default:
        case 0:
            return 0;
        break;
        case 1: //Atak w dol
            {
                licznikTraf = atakDol(offense, target,
                                      idA, idB, My, Oni);
            }
        break;
        case 2: //Atak w prawo
            {
                licznikTraf = atakPrawo(offense, target,
                                      idA, idB, My, Oni);
            }
        break;
        case 3: //Atak w gore
            {
                licznikTraf = atakGora(offense, target,
                                      idA, idB, My, Oni);
            }
        break;
        case 4: //Atak w lewo
            {
                licznikTraf = atakLewo(offense, target,
                                      idA, idB, My, Oni);
            }
        break;
    }

    return licznikTraf;
};

int submarine::atakDol(const Admiral& offense, const Admiral& target,
                       const int& idxA, const int& idxB,
                       const std::vector<std::vector<Pole>>& My,
                       std::vector<std::vector<Pole>>& Oni)
{
    int x = idxA + 1;
    int rozm = Oni.size();
    int idTrafStat = 0;
    int trafienia = 0;

    for (; x < rozm;)
    {
        if (My[x][idxB].getRealStan() > 2)
            return 0; //Nie mozna uzyc torped
        ++x;
    }
    x = 0;

    for (; x < rozm;)
    {
        if (trafienia < 2)
        {
            if (Oni[x][idxB].getRealStan() > 2)
            {
                idTrafStat = Oni[x][idxB].getRealStan();

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

                specTrafHandler(idxA, idxB, offense, Oni);
                ++trafienia;
            }
        }
        else
            x = rozm;
        ++x;
    }
    setActive(false);
    return trafienia; //Sukces - wystrzelono torpedy
};

int submarine::atakPrawo(const Admiral& offense, const Admiral& target,
                       const int& idxA, const int& idxB,
                       const std::vector<std::vector<Pole>>& My,
                       std::vector<std::vector<Pole>>& Oni)
{
    int x = idB + 1;
    int rozm = Oni.size();
    int idTrafStat = 0;
    int trafienia = 0;

    for (; x < rozm;)
    {
        if (My[idxA][x].getRealStan() > 2)
            return 0; //Nie mozna uzyc torped
        ++x;
    }
    x = 0;

    for (; x < rozm;)
    {
        if (trafienia < 2)
        {
            if (Oni[idxA][x].getRealStan() > 2)
            {
                idTrafStat = Oni[idxA][x].getRealStan();

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

                specTrafHandler(idxA, idxB, offense, Oni);
                ++trafienia;
            }
        }
        else
            x = rozm;
        ++x;
    }
    setActive(false);
    return trafienia;
};

int submarine::atakGora(const Admiral& offense, const Admiral& target,
                       const int& idxA, const int& idxB,
                       const std::vector<std::vector<Pole>>& My,
                       std::vector<std::vector<Pole>>& Oni)
{
    int x = idxA - 1;
    int rozm = Oni.size();
    int idTrafStat = 0;
    int trafienia = 0;
    for (; x > 0;)
    {
        if (My[x][idxB].getRealStan() > 2)
            return 0; //Nie mozna uzyc torped
        --x;
    }
    x = rozm - 1;

    for (; x > 0;)
    {
        if (trafienia < 2)
        {
            if (Oni[x][idxB].getRealStan() > 2)
            {
                idTrafStat = Oni[x][idxB].getRealStan();

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

                specTrafHandler(idxA, idxB, offense, Oni);
                ++trafienia;
            }
        }
        else
            x = 0;
        --x;
    }
    setActive(false);
    return trafienia;
};

int submarine::atakLewo(const Admiral& offense, const Admiral& target,
                       const int& idxA, const int& idxB,
                       const std::vector<std::vector<Pole>>& My,
                       std::vector<std::vector<Pole>>& Oni)
{
    int x = idB - 1;
    int rozm = Oni.size();
    int idTrafStat = 0;
    int trafienia = 0;
    for (; x > 0;)
    {
        if (My[idxA][x].getRealStan() > 2)
            return 0; //Nie mozna uzyc torped
        --x;
    }
    x = rozm - 1;

    for (; x > 0;)
    {
        if (trafienia < 2)
        {
            if (Oni[idxA][x].getRealStan() > 2)
            {
                idTrafStat = Oni[idxA][x].getRealStan();

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

                specTrafHandler(idxA, idxB, offense, Oni);
                ++trafienia;
            }
        }
        else
            x = 0;
        --x;
    }
    setActive(false);
    return trafienia;
};

void submarine::trafienie()
{
    jednostka::trafienie();
};
