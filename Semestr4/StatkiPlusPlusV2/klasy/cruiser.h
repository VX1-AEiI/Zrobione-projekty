#ifndef CRUISER_H
#define CRUISER_H
#include "jednostka.h"

class cruiser : public jednostka
{
public:
    cruiser();
    ~cruiser();
    virtual int special(const Admiral&, const Admiral&,
                         const std::vector<std::vector<Pole>>&,
                         std::vector<std::vector<Pole>>&);
    virtual void trafienie();
};

#endif // CRUISER_H
