#include "lotniskowiec.h"

lotniskowiec::lotniskowiec()
    :jednostka("Lotniskowiec", "Nalot", 5) {};

lotniskowiec::~lotniskowiec() {};

int lotniskowiec::special(const Admiral& offense, const Admiral& target,
                            const std::vector<std::vector<Pole>>& My,
                            std::vector<std::vector<Pole>>& Oni)
{
    char wybor {'_'};
    int idxA = 0;
    int idxB = 0;
    int rozm = Oni.size();
    int idTrafStat = 0;
    int liczbaTraf = 0;

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

    if (specTrafControl(offense, target, Oni, idxA, idxB))
        ++liczbaTraf;

    if ((idxA - 1) > -1)
    {
        if (specTrafControl(offense, target, Oni, idxA - 1, idxB))
            ++liczbaTraf;
    }
    if ((idxA + 1) < rozm)
    {
        if (specTrafControl(offense, target, Oni, idxA + 1, idxB))
            ++liczbaTraf;
    }
    if ((idxB - 1) > -1)
    {
        if (specTrafControl(offense, target, Oni, idxA, idxB - 1))
            ++liczbaTraf;
    }
    if ((idxB + 1) < rozm)
    {
        if (specTrafControl(offense, target, Oni, idxA, idxB + 1))
            ++liczbaTraf;
    }
    setActive(false);
    return liczbaTraf;
};

bool lotniskowiec::specTrafControl(const Admiral& offense, const Admiral& target,
                                   std::vector<std::vector<Pole>>& Oni,
                                   const int indexA&, const int indexB&)
{
    int idTrafStat = 0;
    if (Oni[indexA][indexB].getRealStan() > 2)
    {
        idTrafStat = Oni[indexA][indexB].getRealStan();
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
        specTrafHandler(indexA, indexB, offense, Oni);
        ++liczbaTraf;
        return true;
    }
    else
    {
        Oni[indexA][indexB].setRealStan(1);
        Oni[indexA][indexB].setStan(1);
    }
    return false;
};

void lotniskowiec::trafienie()
{
    jednostka::trafienie();
};
