#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
int main()
{
    int y = 0;
    initlistecl();
    initlistech();
    initres();
    while (y != 6)
    {
        y = gestionhotel();
    }
    return 0;
}
