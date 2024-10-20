#include "cruiser.h"

cruiser::cruiser()
    :jednostka("Krazownik","Ostrzal Rakietowy", 4) {};

cruiser::~cruiser() {};

char cruiser::special()
{
    if (getActive())
        return 'K';
    else
        return '\"';
};

void cruiser::trafienie()
{
    jednostka::trafienie();
};
