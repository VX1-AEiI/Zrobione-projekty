#include "lista.h"
#include <iostream>
template <typename D>
Wezel<D>::Wezel(D kontent)
{
    dane = kontent;
    nastepny = nullptr;
};

template <typename D>
Wezel<D>::Wezel()
{
    //dane = NULL;
    nastepny = nullptr;
};

template <typename T>
Lista<T>::Lista(std::initializer_list<T> args)
    : licz_obj(0), poczatek(nullptr)
{
    for (auto x : args)
        push_back(x);
};

template <typename T>
Lista<T>::Lista(const Lista<T>& inna_lista)
    : licz_obj(0), poczatek(nullptr)
{
    licz_obj = inna_lista.licz_obj;
    poczatek = inna_lista.poczatek;
};

template <typename T>
Lista<T>::Lista(Lista<T>&& inna_lista)
    : licz_obj(0), poczatek(nullptr)
{
    licz_obj = inna_lista.licz_obj;
    poczatek = inna_lista.poczatek;

    inna_lista.licz_obj = 0;
    inna_lista.poczatek = nullptr;
};

template <typename T>
Lista<T>::Lista()
{
    licz_obj = 0;
    poczatek = nullptr;
};

template <typename T>
Lista<T>::~Lista()
{
    licz_obj = 0;
    poczatek = nullptr;
};

template <typename T>
bool Lista<T>::empty()
{
    if (licz_obj == 0)
        return true;
    else
        return false;
};

template <typename T>
int Lista<T>::size() { return licz_obj; };

template <typename T>
void Lista<T>::push_back(T kontent)
{
    std::shared_ptr<Wezel<T>> nowy_wezel(new Wezel<T>());
    nowy_wezel->dane = kontent;

    if (poczatek == nullptr)
    {
        poczatek = nowy_wezel;
    }
    else
    {
        std::shared_ptr<Wezel<T>> tempPtr;
        tempPtr = poczatek;

        while (tempPtr->nastepny != nullptr)
            tempPtr = tempPtr->nastepny;

        tempPtr->nastepny = nowy_wezel;
        nowy_wezel->nastepny = nullptr;
    }
    ++licz_obj;
};

template <typename T>
T& Lista<T>::operator[](int indeks)
{
    std::shared_ptr<Wezel<T>> tempPtr;
    tempPtr = poczatek;

    if (indeks < licz_obj)
    {
        for (int a = 0; a < indeks; a++)
        {
            tempPtr = tempPtr->nastepny;
        }
    }
    return tempPtr->dane;
};

template <typename T>
Lista<T>& Lista<T>::operator=(Lista<T>&& inna_lista)
{
    if (*this != inna_lista)
    {
        licz_obj = inna_lista.licz_obj;
        poczatek = inna_lista.poczatek;

        inna_lista.licz_obj = 0;
        inna_lista.poczatek = nullptr;
    }
    return *this;
};

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& inna_lista)
{
    licz_obj = inna_lista.licz_obj;
    poczatek = inna_lista.poczatek;

    return *this;
};

template <typename T>
bool Lista<T>::operator!=(const Lista<T>& inna_lista)
{
    if (poczatek == inna_lista.poczatek)
        return false;
    else
        return true;
};
