#ifndef CRUISER_H
#define CRUISER_H
#include "jednostka.h"

class cruiser : public jednostka
{
    public:
    cruiser();
    ~cruiser();
    virtual char special();
    virtual void trafienie();
};

#endif // CRUISER_H
