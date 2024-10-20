#include "lotniskowiec.h"

lotniskowiec::lotniskowiec()
    :jednostka("Lotniskowiec", "Nalot", 5) {};

lotniskowiec::~lotniskowiec() {};

char lotniskowiec::special()
{
    if (getActive())
        return 'L';
    else
        return '\"';
};

void lotniskowiec::trafienie()
{
    jednostka::trafienie();
};
