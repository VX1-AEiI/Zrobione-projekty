#ifndef NISZCZYCIEL_H
#define NISZCZYCIEL_H

#include "jednostka.h"


class niszczyciel : public jednostka
{
public:
    niszczyciel();
    ~niszczyciel();
    virtual char special();
    virtual void trafienie();
};

#endif // NISZCZYCIEL_H
