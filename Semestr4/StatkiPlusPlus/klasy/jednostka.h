#ifndef JEDNOSTKA_H
#define JEDNOSTKA_H
#include <string>

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

    public:
    jednostka(std::string, std::string, int, bool) = delete;
    jednostka(std::string, std::string, int);
    jednostka(std::string, std::string) = delete;
    jednostka(std::string) = delete;
    jednostka() = delete;
    virtual ~jednostka();
    virtual char special() = 0; //Na wypadek jeszcze innej aranzacji gry
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
