#ifndef LOTNISKOWIEC_H
#define LOTNISKOWIEC_H

#include "jednostka.h"


class lotniskowiec : public jednostka
{
public:
    lotniskowiec();
    ~lotniskowiec();
    virtual char special();
    virtual void trafienie();
};

#endif // LOTNISKOWIEC_H
