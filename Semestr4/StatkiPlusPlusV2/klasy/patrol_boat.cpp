#include "patrol_boat.h"

patrol_boat::patrol_boat()
 :jednostka("Lodz patrolowa", "Zwiad", 2) {};

patrol_boat::~patrol_boat() {};

int patrol_boat::special(const Admiral& offense, const Admiral& target,
                         const std::vector<std::vector<Pole>>& My,
                         std::vector<std::vector<Pole>>& Oni)
{
    char wybor {'_'};
    int idxA {0}, idxB {0};

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

    Oni[idxA-1][idxB-1].reveal();
    Oni[idxA-1][idxB].reveal();
    Oni[idxA-1][idxB+1].reveal();
    Oni[idxA][idxB-1].reveal();
    Oni[idxA][idxB].reveal();
    Oni[idxA][idxB+1].reveal();
    Oni[idxA+1][idxB-1].reveal();
    Oni[idxA+1][idxB].reveal();
    Oni[idxA+1][idxB+1].reveal();

    setActive(false);
    return 0;
};

void patrol_boat::trafienie()
{
    jednostka::trafienie();
};
