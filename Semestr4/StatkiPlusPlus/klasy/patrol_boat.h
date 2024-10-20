#ifndef PATROL_BOAT_H
#define PATROL_BOAT_H

#include "jednostka.h"


class patrol_boat : public jednostka
{
public:
    patrol_boat();
    ~patrol_boat();
    virtual char special();
    virtual void trafienie();
};

#endif // PATROL_BOAT_H
