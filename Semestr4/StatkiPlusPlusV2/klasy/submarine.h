#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "jednostka.h"


class submarine : public jednostka
{
private:
    int atakGora(const Admiral&, const Admiral&,
                 const int&, const int&,
                const std::vector<std::vector<Pole>>&,
                std::vector<std::vector<Pole>>&);
    int atakLewo(const Admiral&, const Admiral&,
                 const int&, const int&,
                const std::vector<std::vector<Pole>>&,
                std::vector<std::vector<Pole>>&);
    int atakPrawo(const Admiral&, const Admiral&,
                 const int&, const int&,
                const std::vector<std::vector<Pole>>&,
                std::vector<std::vector<Pole>>&);
    int atakDol(const Admiral&, const Admiral&,
                 const int&, const int&,
                const std::vector<std::vector<Pole>>&,
                std::vector<std::vector<Pole>>&);

public:
    submarine();
    ~submarine();
    virtual int special(const Admiral&, const Admiral&,
                         const std::vector<std::vector<Pole>>&,
                         std::vector<std::vector<Pole>>&);
    virtual void trafienie();
};

#endif // SUBMARINE_H
