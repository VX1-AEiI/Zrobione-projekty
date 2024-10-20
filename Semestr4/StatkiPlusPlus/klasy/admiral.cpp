#include "admiral.h"

Admiral::Admiral(const std::string& name)
{
    imie = name;
    totalHP = 0;
    trafienia = 0;
    flota.clear();
    flota.push_back(new patrol_boat());
    flota.push_back(new submarine());
    flota.push_back(new niszczyciel());
    flota.push_back(new cruiser());
    flota.push_back(new lotniskowiec());

    for (auto statek : flota)
        { totalHP += statek->getCurrHP(); }
};

Admiral::Admiral()
{
    imie = "";
    flota.clear();
    totalHP = 0;
    trafienia = 0;
    flota.push_back(new patrol_boat());
    flota.push_back(new submarine());
    flota.push_back(new niszczyciel());
    flota.push_back(new cruiser());
    flota.push_back(new lotniskowiec());

    for (auto statek : flota)
        { totalHP += statek->getCurrHP(); }
};

Admiral::~Admiral()
{
    imie = "";
    flota.clear();
    totalHP = 0;
    trafienia = 0;
};

Admiral::Admiral(const Admiral& kapitan)
{
    imie = kapitan.imie;
    flota = kapitan.flota;
    totalHP = kapitan.totalHP;
};

Admiral::Admiral(Admiral&& kapitan)
{
    imie = kapitan.imie;
    flota = kapitan.flota;
    totalHP = kapitan.totalHP;

    kapitan.imie = "";
    kapitan.flota.clear();
    kapitan.totalHP = 0;
};

void Admiral::setImie(const std::string& in) { imie = in; };
std::string Admiral::getImie() { return imie; };
int Admiral::getTotalHP() { return totalHP; };

void Admiral::setSail(const int& okret, const int& direction)
{
    if (flota[okret] != nullptr)
        flota[okret] -> setKierunek(direction);
};

int Admiral::getSail(const int& okret)
{
    int tmp = 0;
    if(flota[okret] != nullptr)
        tmp = flota[okret] -> getKierunek();
    return tmp;
};

void Admiral::incTraf() { ++trafienia; };
int Admiral::getTraf() { return trafienia; };

void Admiral::ouch(const int& okret)
{
    if(flota[okret] != nullptr)
    {
        flota[okret] -> trafienie();
        --totalHP;
    }
};

std::string Admiral::outSpecName(const int& idx)
{
    std::string tmp {""};
    if (flota[idx] != nullptr)
         tmp = flota[idx] -> getAtakName();
    return tmp;
};

void Admiral::usedSpec(const int& idx)
{
    if (flota[idx] != nullptr)
        flota[idx] -> setActive(false);
};

bool Admiral::czyMoznaUzycSpec(const int& idx)
{
    if (flota[idx] != nullptr)
        return flota[idx] -> getActive();
    return false;
};

void Admiral::znajdzStatek(const int& statek, int& idA, int& idB)
{
    idA = flota[statek]->getIndexA();
    idB = flota[statek]->getIndexB();
};

void Admiral::ustawStatek(const int& okr, const int& idA, const int& idB)
{
    if (flota[okr] != nullptr)
        flota[okr] -> setLocation(idA, idB);
};

Admiral Admiral::operator--(int)
{
    Admiral temp = *this;
    --*this;
    return temp;
};

Admiral& Admiral::operator--()
{
    if (totalHP > 0)
        --totalHP;
    return *this;
};

Admiral& Admiral::operator=(const Admiral& kapitan)
{
    if (this != &kapitan)
    {
    imie = kapitan.imie;
    flota = kapitan.flota;
    totalHP = kapitan.totalHP;
    }

    return *this;
};

Admiral& Admiral::operator=(Admiral&& kapitan)
{
    if (this != &kapitan)
    {
        imie = kapitan.imie;
        flota = kapitan.flota;
        totalHP = kapitan.totalHP;

        kapitan.imie = "";
        kapitan.flota.clear();
        kapitan.totalHP = 0;
    }
    return *this;
};
