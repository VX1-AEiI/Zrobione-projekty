#include "niszczyciel.h"

niszczyciel::niszczyciel()
    :jednostka::jednostka("Niszczyciel", "Salwa torpedowa", 3) {};

niszczyciel::~niszczyciel() {};

char niszczyciel::special()
{
    if (getActive())
        return 'N';
    else
        return '\"';
};

void niszczyciel::trafienie()
{
    jednostka::trafienie();
};
