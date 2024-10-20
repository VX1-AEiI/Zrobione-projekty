#ifndef JEDNOSTKA_H
#define JEDNOSTKA_H
#include <string>
#include <vector>
#include "admiral.h"
#include "pole.h"

class jednostka
{
    private:
    std::string unitName;
    std::string atakName;
    bool specActive;
    short int kierunek;
    int indeksA;
    int indeksB;
    int hitPoints;

    protected:
    bool validPole(const int&, const int&, const std::vector<std::vector<Pole>>&);
    void specTrafHandler(const int&, const int&,
                         const Admiral&, std::vector<std::vector<Pole>>&);
    void specUnitGotHit(const int&, const Admiral&);

    public:
    jednostka(std::string, std::string, int, bool) = delete;
    jednostka(std::string, std::string, int);
    jednostka(std::string, std::string) = delete;
    jednostka(std::string) = delete;
    jednostka() = delete;

    virtual ~jednostka();
    virtual int special(const Admiral&, const Admiral&,
                         const std::vector<std::vector<Pole>>&,
                         std::vector<std::vector<Pole>>&) = 0;
    virtual void trafienie() = 0;
    virtual bool getActive();
    virtual void setActive(const bool);
    virtual std::string getAtakName();
    virtual int getCurrHP();
    virtual void setKierunek(const short int&);
    virtual int getKierunek();
    virtual void setLocation(const int&, const int&);
    virtual int getIndexA();
    virtual int getIndexB();
};

#endif // JEDNOSTKA_H
