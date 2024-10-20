#ifndef PATROL_BOAT_H
#define PATROL_BOAT_H
#include "jednostka.h"


class patrol_boat : public jednostka
{
public:
    patrol_boat();
    ~patrol_boat();
    virtual int special(const Admiral&, const Admiral&,
                         const std::vector<std::vector<Pole>>&,
                         std::vector<std::vector<Pole>>&);
    virtual void trafienie();
};

#endif // PATROL_BOAT_H
