#include "niszczyciel.h"

niszczyciel::niszczyciel()
    :jednostka::jednostka("Niszczyciel", "Salwa torpedowa", 3) {};

niszczyciel::~niszczyciel() {};

int niszczyciel::special(const Admiral& offense, const Admiral& target,
                         const std::vector<std::vector<Pole>>& My,
                         std::vector<std::vector<Pole>>& Oni)
{
    int rozmPln = My.size();
    short int kierA = 0;
    short int kierB = 0;
    short int trafA = 3;
    short int trafB = 3;
    bool aAtakMid = true;
    bool aAtakOff1 = true;
    bool aAtakOff2 = true;
    bool bAtakMid = true;
    bool bAtakOff1 = true;
    bool bAtakOff2 = true;
    int liczbaTraf = 0;

    switch (kierunek)
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
        return 0;
        break;
    }

    switch (kierA)
    {
    default:
        return 0;
        break;
    case 1:
        {
            aAtakMid = checkLinieStrzaluW(indeksB, My);
            aAtakOff1 = checkLinieStrzaluW(indeksB + 1, My);
            aAtakOff2 = checkLinieStrzaluW(indeksB + 2, My);
        }
        break;
    case 2:
        {
            aAtakMid = checkLinieStrzaluA(indeksA, My);
            aAtakOff1 = checkLinieStrzaluA(indeksA - 1, My);
            aAtakOff2 = checkLinieStrzaluA(indeksA - 2, My);
        }
        break;
    case 3:
        {
            aAtakMid = checkLinieStrzaluS(indeksB, My);
            aAtakOff1 = checkLinieStrzaluS(indeksB - 1, My);
            aAtakOff2 = checkLinieStrzaluS(indeksB - 2, My);
        }
        break;
    case 4:
        {
            aAtakMid = checkLinieStrzaluD(indeksA, My);
            aAtakOff1 = checkLinieStrzaluD(indeksA + 1, My);
            aAtakOff2 = checkLinieStrzaluD(indeksA + 2, My);
        }
        break;
    }
    trafA = checkLiczbeAtakow(aAtakMid, aAtakOff1, aAtakOff2);

    switch (kierB)
    {
    default:
        return 0;
        break;
    case 1:
        {
            bAtakMid = checkLinieStrzaluW(indeksB, My);
            bAtakOff1 = checkLinieStrzaluW(indeksB - 1, My);
            bAtakOff2 = checkLinieStrzaluW(indeksB - 2, My);
        }
        break;
    case 2:
        {
            bAtakMid = checkLinieStrzaluA(indeksA, My);
            bAtakOff1 = checkLinieStrzaluA(indeksA + 1, My);
            bAtakOff2 = checkLinieStrzaluA(indeksA + 2, My);
        }
        break;
    case 3:
        {
            bAtakMid = checkLinieStrzaluS(indeksB, My);
            bAtakOff1 = checkLinieStrzaluS(indeksB + 1, My);
            bAtakOff2 = checkLinieStrzaluS(indeksB + 2, My);
        }
        break;
    case 4:
        {
            bAtakMid = checkLinieStrzaluD(indeksA, My);
            bAtakOff1 = checkLinieStrzaluD(indeksA - 1, My);
            bAtakOff2 = checkLinieStrzaluD(indeksA - 2, My);
        }
        break;
    }
    trafB = checkLiczbeAtakow(bAtakMid, bAtakOff1, bAtakOff2);

    if ((trafA + trafB) == 0)
        return 0;

    if (trafA > trafB)
    {
        switch (kierA)
        {
        default:
        case 0:
            return 0;
            break;
        case 1:
            {
                if (atakujW(indeksB, aAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujW(indeksB+1, aAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujW(indeksB+2, aAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        case 2:
            {
                if (atakujA(indeksA, aAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujA(indeksA-1, aAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujA(indeksA-2, aAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        case 3:
            {
                if (atakujS(indeksB, aAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujS(indeksB-1, aAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujS(indeksB-2, aAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        case 4:
            {
                if (atakujD(indeksA, aAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujD(indeksA+1, aAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujD(indeksA+2, aAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        }
    }
    else
    {
        switch (kierB)
        {
        default:
        case 0:
            return 0;
            break;
        case 1:
            {
                if (atakujW(indeksB, bAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujW(indeksB-1, bAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujW(indeksB-2, bAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        case 2:
            {
                if (atakujA(indeksA, bAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujA(indeksA+1, bAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujA(indeksA+2, bAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        case 3:
            {
                if (atakujS(indeksA, bAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujS(indeksA+1, bAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujS(indeksA+2, bAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        case 4:
            {
                if (atakujD(indeksB, bAtakMid, offense, target, Oni)) ++liczbaTraf;
                if (atakujD(indeksB-1, bAtakOff1, offense, target, Oni)) ++liczbaTraf;
                if (atakujD(indeksB-2, bAtakOff2, offense, target, Oni)) ++liczbaTraf;
            }
            break;
        }
    }

    return liczbaTraf;
};

void niszczyciel::trafienie()
{
    jednostka::trafienie();
};

bool niszczyciel::checkLinieStrzaluW(const int& idxB, const std::vector<std::vector<Pole>>& My)
{
    int x = indeksA - 1;
    for (; x > 0;)
    {
        if (My[x][idxB].getRealStan() > 2)
        {
            return false;
        }
        --x;
    }
    return true;
};

bool niszczyciel::checkLinieStrzaluA(const int& idxA, const std::vector<std::vector<Pole>>& My)
{
    int x = indeksB - 1;
    for (; x > 0;)
    {
        if (My[idxA][x].getRealStan() > 2)
        {
            return false;
        }
        --x;
    }
    return true;
};

bool niszczyciel::checkLinieStrzaluS(const int& idxB, const std::vector<std::vector<Pole>>& My)
{
    int x = indeksA + 1;
    int rozmPln = My.size();
    for (; x < rozmPln;)
    {
        if (My[x][idxB].getRealStan() > 2)
        {
            return false;
        }
        ++x;
    }
    return true;
};

bool niszczyciel::checkLinieStrzaluD(const int& idxA, const std::vector<std::vector<Pole>>& My)
{
    int x = indeksB + 1;
    int rozmPln = My.size();
    for (; x < rozmPln;)
    {
        if (My[idxA][x].getRealStan() > 2)
        {
            return false;
        }
        ++x;
    }
    return true;
};

short int niszczyciel::checkLiczbeAtakow(const bool& atakMid, const bool& atakOff1, const bool& atakOff2)
{
    short int mozliweTrafienia = 0;

    if (atakMid) ++mozliweTrafienia;
    if (atakOff1) ++mozliweTrafienia;
    if (atakOff2) ++mozliweTrafienia;

    return mozliweTrafienia;
};

bool niszczyciel::atakujW(const int& idxB, const bool& warunek, const Admiral& offense,
                          const Admiral& target, const std::vector<std::vector<Pole>>& Oni)
{
    int x = Oni.size() - 1;
    int kod_pola = 0;
    if (warunek)
    {
        for (; x > 0;)
        {
            kod_pola = Oni[x][idxB].getRealStan();
            if (kod_pola > 2)
            {
                specUnitGotHit(kod_pola, target);
                specTrafHandler(x, idxB, offense, Oni);
                return true;
            }
            --x;
        }
    }
    return false;
};

bool niszczyciel::atakujA(const int& idxA, const bool& warunek, const Admiral& offense,
                          const Admiral& target, const std::vector<std::vector<Pole>>& Oni)
{
    int x = Oni.size() - 1;
    int kod_pola = 0;
    if (warunek)
    {
        for (; x > 0;)
        {
            kod_pola = Oni[idxA][x].getRealStan();
            if (kod_pola > 2)
            {
                specUnitGotHit(kod_pola, target);
                specTrafHandler(idxA, x, offense, Oni);
                return true;
            }
            --x;
        }
    }
    return false;
};

bool niszczyciel::atakujS(const int& idxB, const bool& warunek, const Admiral& offense,
                          const Admiral& target, const std::vector<std::vector<Pole>>& Oni)
{
    int x = 0;
    int rozmPln = Oni.size();
    int kod_pola = 0;
    if (warunek)
    {
        for (; x < rozmPln;)
        {
            kod_pola = Oni[x][idxB].getRealStan();
            if (kod_pola > 2)
            {
                specUnitGotHit(kod_pola, target);
                specTrafHandler(x, idxB, offense, Oni);
                return true;
            }
            ++x;
        }
    }
    return false;
};

bool niszczyciel::atakujD(const int& idxA, const bool& warunek, const Admiral& offense,
                          const Admiral& target, const std::vector<std::vector<Pole>>& Oni)
{
    int x = 0;
    int rozmPln = Oni.size();
    int kod_pola = 0;
    if (warunek)
    {
        for (; x < rozmPln;)
        {
            kod_pola = Oni[idxA][x].getRealStan();
            if (kod_pola > 2)
            {
                specUnitGotHit(kod_pola, target);
                specTrafHandler(idxA, x, offense, Oni);
                return true;
            }
            ++x;
        }
    }
    return false;
};
