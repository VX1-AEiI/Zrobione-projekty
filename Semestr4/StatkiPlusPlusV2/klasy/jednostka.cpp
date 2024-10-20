#include "jednostka.h"

jednostka::jednostka(std::string name, std::string desc, int HP)
{
    specActive = true;
    unitName = name;
    atakName = desc;
    hitPoints = HP;
    kierunek = 0;
    indeksA = 0;
    indeksB = 0;
};

jednostka::~jednostka()
{
    specActive = false;
    unitName = "";
    atakName = "";
    hitPoints = 0;
    kierunek = 0;
    indeksA = 0;
    indeksB = 0;
};

bool jednostka::checkPole(const int& idxA, const int& idxB,
                         const std::vector<std::vector<Pole>>& Plansza)
{
    int rozmiarPlanszy = Plansza.size();
    if (idxA > rozmiarPlanszy)
        return false;
    else if (idxA < 0)
        return false;
    if (idxB > rozmiarPlanszy)
        return false;
    else if (idxB < 0)
        return false;

    return true;
};

void jednostka::specTrafHandler(const int& idxA, const int& idxB,
                                const Admiral& offense, std::vector<std::vector<Pole>>& Oni)
{
    Oni[idxA][idxB].setStan(2);
    Oni[idxA][idxB].setRealStan(2);
    offense.incTraf();
};

void jednostka::specUnitGotHit(const int& kod_pola, const Admiral& target)
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
};

void jednostka::trafienie()
{
    --hitPoints;
    if (hitPoints < 1)
        specActive = false;
};
bool jednostka::getActive() {return specActive; };
void jednostka::setActive(const bool x) { specActive = x; };
std::string jednostka::getAtakName() {return atakName; };
int jednostka::getCurrHP() {return hitPoints; };

void jednostka::setKierunek(const short int& direction)
{
    switch (direction)
    {
    case 1:
        { kierunek = 1; } //W
        break;
    case 2:
        { kierunek = 2; } //A
        break;
    case 3:
        { kierunek = 3; } //S
        break;
    case 4:
        { kierunek = 4; } //D
        break;
    case 0:
    default:
        { kierunek = 0; }
        break;
    }
};
int jednostka::getKierunek() {return kierunek; };

void jednostka::setLocation(const int& idxA, const int& idxB)
{
    indeksA = idxA;
    indeksB = idxB;
};

int jednostka::getIndexA() {return indeksA; };
int jednostka::getIndexB() {return indeksB; };
