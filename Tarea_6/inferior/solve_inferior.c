/*Giovanny Encinia*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
/*#include "sumatoria/sumatoria.h"*/
#define ZERO 0
#define ONE 1
#define TWO 2

double sumatoria_i(double **matrix,  double *x, int i, \
  int n, int begin, int end, int gap)
{
    double sum = ZERO;
    int j = begin;

    while(j <= end)
    {
        sum += (*(*(matrix+i) + j + gap)) * (*(x + j));
        j++;
    }

        return sum;

}

void solve_triangular_infer(double **matrix, int rows, \
    int cols, double *x, double *y)
{
    /*
    i = {1, 2, ..., n}
    xi = \frac{1}{matriz[i][i]} * (yi - \sum_{j = 1}^{i}matrix[i][j]*x[j])
    */

    int i = ZERO;

    if(cols != rows)
    {
        printf("No se puede sollucionar, no es matriz cuadrada\n");
        x = NULL;
    }
    else
    {

        while(i < rows)
        {
            if(*(*(matrix + i)) == 0)
            {
                printf("0 en diagonal no hay solucion\n");
                x = NULL;
            }

            i++;

        }

        /*el ultimo termino es rows-ONE*/
        *(x) = *(y)/ (*(*(matrix)));

        i = ONE;

        while(i < rows)
        {

            *(x + i) =  ((*(y + i)) - sumatoria_i(matrix, x, i,rows, ZERO, i - ONE, ZERO)) / *(*(matrix+i) + i);
            i++;
        }

    }

}
