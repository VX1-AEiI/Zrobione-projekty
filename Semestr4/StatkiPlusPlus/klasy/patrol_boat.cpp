#include "patrol_boat.h"

patrol_boat::patrol_boat()
 :jednostka("Lodz patrolowa", "Zwiad", 2) {};

patrol_boat::~patrol_boat() {};

char patrol_boat::special()
{
    if (getActive())
        return 'P';
    else
        return '\"';
};

void patrol_boat::trafienie()
{
    jednostka::trafienie();
};
