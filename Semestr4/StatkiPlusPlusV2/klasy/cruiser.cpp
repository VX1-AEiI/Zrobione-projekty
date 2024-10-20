#include "cruiser.h"

cruiser::cruiser()
    :jednostka("Krazownik","Ostrzal Rakietowy", 4) {};

cruiser::~cruiser() {};

int cruiser::special(const Admiral& offense, const Admiral& target,
                    const std::vector<std::vector<Pole>>& My,
                    std::vector<std::vector<Pole>>& Oni)
{
    std::vector<std::pair<int, int>> targetsVec;
    std::vector<std::pair<int, int>> niewiadome;
    int pustePola = 0;
    int tmp = 0;
    int x = 0;
    int idA = 0;
    int idB = 0;
    int rozmPln = Oni.size();
    int licznikTraf = 0;

    for (int i = 0; i < rozmPln;)
    {
        for (int j = 0; j < rozmPln;)
        {
            if (Oni[i][j].getStan() > 2)
            {
                targetsVec.push_back({i, j});
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

    tmp = targetsVec.size();
    if (tmp > 4)
        tmp = 4;

    for (; x < tmp ;)
    {
        idA = targetsVec[x].first;
        idB = targetsVec[x].second;

        int okret = Oni[idA][idB].getRealStan();

        switch (okret)
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

        specTrafHandler(idA, idB, offense, Oni);
        ++licznikTraf;
        ++x;
    }

    for (; x < pustePola;)
    {
        int wybor = 0;
        int statek = 0;
        idA = 0;
        idB = 0;

        do{
            wybor = rand() % niewiadome.size();

            idA = niewiadome[wybor].first;
            idB = niewiadome[wybor].second;
            statek = Oni[idA][idB].getStan();
        } while (statek != 0);

        statek = Oni[idA][idB].getRealStan();

        switch (statek)
        {
        default:
        case 0:
            {
                Oni[idA][idB].setStan(1);
                Oni[idA][idB].setRealStan(1);
            }
            break;
        case 3:
            {
                specTrafHandler(idA, idB, offense, Oni);
                target.ouch(0);
                ++licznikTraf;
            }
            break;
        case 4:
        case 5:
            {
                specTrafHandler(idA, idB, offense, Oni);
                target.ouch(2);
                ++licznikTraf;
            }
            break;
        case 6:
        case 7:
            {
                specTrafHandler(idA, idB, offense, Oni);
                tgt.ouch(1);
                ++licznikTraf;
            }
            break;
        case 8:
            {
                specTrafHandler(idA, idB, offense, Oni);
                tgt.ouch(3);
                ++licznikTraf;
            }
            break;
        case 9:
            {
                specTrafHandler(idA, idB, offense, Oni);
                tgt.ouch(4);
                ++licznikTraf;
            }
            break;
        }
        ++x;
    }
    setActive(false);
    return licznikTraf;
};

void cruiser::trafienie()
{
    jednostka::trafienie();
};
