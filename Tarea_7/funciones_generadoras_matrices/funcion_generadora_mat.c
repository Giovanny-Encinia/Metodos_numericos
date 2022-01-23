#include <stdio.h>
#define ZERO 0
#define ONE 1
#define TWO 2

double funcion_generadora_1(int i, int j)
{
    /*
    Se necesita saber las coordenadas dentro de la matriz
    para poder generar un valor
    a_{i, j} = {2 if i=j; -1 if i=j+1 or i=j-1; 0 otro
    */

    if(i == j)
        return TWO;

    if((i == j + ONE) || (i == j - ONE))
        return -ONE;

    return ZERO;

}

