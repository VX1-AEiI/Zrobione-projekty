#include "interfejs.h"
#include <iostream>
//Autor: Braian Nowak
int main()
{
    std::cout << "Hello :)" << std::endl;

    Interfejs SudokuCMD;
    SudokuCMD.wczytPref();
    SudokuCMD.menuGlowne();

    return 0;
}
