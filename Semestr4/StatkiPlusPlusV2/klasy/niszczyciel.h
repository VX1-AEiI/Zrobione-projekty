#ifndef NISZCZYCIEL_H
#define NISZCZYCIEL_H

#include "jednostka.h"


class niszczyciel : public jednostka
{
private:
    bool checkLinieStrzaluW(const int&, const std::vector<std::vector<Pole>>&);
    bool checkLinieStrzaluA(const int&, const std::vector<std::vector<Pole>>&);
    bool checkLinieStrzaluS(const int&, const std::vector<std::vector<Pole>>&);
    bool checkLinieStrzaluD(const int&, const std::vector<std::vector<Pole>>&);

    bool atakujW(const int&, const bool&, const Admiral&, const Admiral&, const std::vector<std::vector<Pole>>&);
    bool atakujA(const int&, const bool&, const Admiral&, const Admiral&, const std::vector<std::vector<Pole>>&);
    bool atakujS(const int&, const bool&, const Admiral&, const Admiral&, const std::vector<std::vector<Pole>>&);
    bool atakujD(const int&, const bool&, const Admiral&, const Admiral&, const std::vector<std::vector<Pole>>&);

    short int checkLiczbeAtakow(const bool&, const bool&, const bool&);

public:
    niszczyciel();
    ~niszczyciel();
    virtual int special(const Admiral&, const Admiral&,
                         const std::vector<std::vector<Pole>>&,
                         std::vector<std::vector<Pole>>&);
    virtual void trafienie();
};

#endif // NISZCZYCIEL_H
