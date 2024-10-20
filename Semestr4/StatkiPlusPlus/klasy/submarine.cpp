#include "submarine.h"

submarine::submarine()
    :jednostka::jednostka("Lodz podwodna", "Dwie torpedy", 3) {};

submarine::~submarine() {};

char submarine::special()
{
    if (getActive())
        return 'S';
    else
        return '\"';
};

void submarine::trafienie()
{
    jednostka::trafienie();
};
