#ifndef GRAPLUSPLUS_H
#define GRAPLUSPLUS_H
#include "gra.h"

class graPlusPlus : public Gra
{
    private:
    void specialAttackTrafAnnouncement(const int&, const std::string&);

    void menuGraczaUI();

    public:
    graPlusPlus(const std::string&, const std::string&, bool, bool);
    graPlusPlus() = delete;
    ~graPlusPlus();

    void rozgrywka();
    void ekranWygranej(const bool&, const std::string&);
    std::string menuAtaku();

    void zapiszStatystyki(std::string&, int&, std::string&, int&);
};

#endif // GRAPLUSPLUS_H
