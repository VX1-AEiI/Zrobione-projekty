#ifndef LOTNISKOWIEC_H
#define LOTNISKOWIEC_H

#include "jednostka.h"


class lotniskowiec : public jednostka
{
private:
    bool specTrafControl(const Admiral&, const Admiral&,
                         const std::vector<std::vector<Pole>>&,
                         const int&, const int&);

public:
    lotniskowiec();
    ~lotniskowiec();
    virtual int special(const Admiral&, const Admiral&,
                         const std::vector<std::vector<Pole>>&,
                         std::vector<std::vector<Pole>>&);
    virtual void trafienie();
};

#endif // LOTNISKOWIEC_H
