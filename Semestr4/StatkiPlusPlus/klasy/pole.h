#ifndef POLE_H
#define POLE_H


class Pole
{
    private:
    int rzeczywisty_stan;
    int stan;

    public:
    Pole(int);
    Pole();
    ~Pole();

    int getStan() const;
    int getRealStan() const;
    void setStan(int);
    void setRealStan(int);
    void reveal();
};

#endif // POLE_H
