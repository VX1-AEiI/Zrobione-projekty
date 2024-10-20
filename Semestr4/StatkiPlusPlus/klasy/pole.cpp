#include "pole.h"

Pole::Pole(int x)
{
    rzeczywisty_stan = x;
    stan = 0;
};

Pole::Pole()
{
    rzeczywisty_stan = 0;
    stan = 0;
};

Pole::~Pole()
{
    rzeczywisty_stan = 0;
    stan = 0;
};

int Pole::getStan() const { return stan;};
int Pole::getRealStan() const { return rzeczywisty_stan;};

void Pole::setStan(int vartosc)
{
    if (vartosc < 0)
        stan = 0;
    else if (vartosc > 9)
        stan = 0;
    else
        stan = vartosc;
};

void Pole::setRealStan(int vartosc)
{
    if (vartosc < 0)
        rzeczywisty_stan = 0;
    else if (vartosc > 9)
        rzeczywisty_stan = 0;
    else
        rzeczywisty_stan = vartosc;
}

void Pole::reveal() { stan = rzeczywisty_stan; };
