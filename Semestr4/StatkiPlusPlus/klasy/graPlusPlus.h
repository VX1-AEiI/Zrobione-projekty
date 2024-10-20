#ifndef GRAPLUSPLUS_H
#define GRAPLUSPLUS_H
#include "gra.h"

class graPlusPlus : public Gra
{
    //private:

    public:
    graPlusPlus(const std::string&, const std::string&, bool, bool);
    graPlusPlus() = delete;
    ~graPlusPlus();

    void rozgrywka();
    void menuGracza();
    void ekranWygranej(bool, const std::string&);
    std::string menuAtaku();

    void specialPatrol(std::vector<std::vector<Pole>>&);
    bool specialSub(Admiral&, Admiral&,
                    std::vector<std::vector<Pole>>&,
                    std::vector<std::vector<Pole>>&);
    bool specialDestr(Admiral&, Admiral&,
                      std::vector<std::vector<Pole>>&,
                      std::vector<std::vector<Pole>>&);
    void specialCruis(Admiral&, Admiral&, std::vector<std::vector<Pole>>&);
    void specialAir(Admiral&, Admiral&, std::vector<std::vector<Pole>>&);

    void zapiszStatystyki(std::string&, int&, std::string&, int&);
};

#endif // GRAPLUSPLUS_H
