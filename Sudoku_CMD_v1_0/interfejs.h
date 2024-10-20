#ifndef INTERFEJS_H
#define INTERFEJS_H

class Interfejs {
    bool koloroweUI;
    bool pokazujBledy;

public:

    Interfejs();
    ~Interfejs();

    void czyscCMD();
    //UI

    void menuGlowne();

    void submenuPref();
    void submenuNowaGra();

    //Ustawienia
    void zmienKolorUI();
    void zmienPokazBledow();
    void zapiszPref();
    void wczytPref();
};
#endif // INTERFEJS_H
