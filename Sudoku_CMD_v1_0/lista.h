#ifndef LISTA_H
#define LISTA_H
#include <memory>

template <typename D>
class Wezel {
public:
    D dane;
    std::shared_ptr<Wezel<D>> nastepny;

    Wezel(D);
    Wezel();
};

template <typename T>
class Lista {
    int licz_obj;
    std::shared_ptr<Wezel<T>> poczatek;

public:
    Lista(std::initializer_list<T>);
    Lista(const Lista<T>&);
    Lista(Lista<T>&&);
    Lista();
    ~Lista();

    bool empty();
    int size();
    void push_back(T);

    T& operator[](int);
    Lista<T>& operator=(Lista<T>&&);
    Lista<T>& operator=(const Lista<T>&);
    bool operator!=(const Lista<T>&);
};
#endif // LISTA_H
