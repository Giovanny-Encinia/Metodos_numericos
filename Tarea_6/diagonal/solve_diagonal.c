/*Giovanny Encinia*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define ZERO 0
#define ONE 1
#define TWO 2

void solve_diagonal(double **matrix, int size, double *x, double *y)
{
    /*Solve diagonal matrix
    Parametos
    ===========
    size: es el tamanio de los datos
    x: es un puntero que indica las soluciones
    y: es a lo que la ecuacion matricial es igual

    array*x = y
    */

    int i = ZERO;

    while(i < size)
    {
        *(x + i) = *(y + i) / **(matrix + i);
        i++;
    }

}
