#ifndef ADMIRAL_H
#define ADMIRAL_H
#include <vector>
#include <memory>
#include "patrol_boat.h"
#include "submarine.h"
#include "niszczyciel.h"
#include "cruiser.h"
#include "lotniskowiec.h"

class Admiral
{
    private:
    std::string imie;
    std::vector<jednostka*> flota;
    int totalHP;
    int trafienia;

    public:
    Admiral(const std::string&);
    Admiral();
    ~Admiral();

    Admiral(const Admiral&); //Kopiujacy
    Admiral(Admiral&&);

    void setImie(const std::string&);
    std::string getImie();
    int getTotalHP();
    void setSail(const int&, const int&);
    int getSail(const int&);
    void incTraf();
    int getTraf();

    void ouch(const int&);
    std::string outSpecName(const int&);
    void usedSpec(const int&);
    bool czyMoznaUzycSpec(const int&);
    void znajdzStatek(const int&, int&, int&);
    void ustawStatek(const int&, const int&, const int&);

    Admiral operator--(int);
    Admiral& operator--();

    Admiral& operator=(const Admiral&); //Kopiujacy
    Admiral& operator=(Admiral&&);
};

#endif // ADMIRAL_H
