#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "jednostka.h"


class submarine : public jednostka
{
public:
    submarine();
    ~submarine();
    virtual char special();
    virtual void trafienie();
};

#endif // SUBMARINE_H
