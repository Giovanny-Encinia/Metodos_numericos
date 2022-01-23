/*Giovanny Encinia*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
/*#include "sumatoria/sumatoria.h"*/
#define ZERO 0
#define ONE 1
#define TWO 2

double sumatoria(double **matrix,  double *x, int i, \
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

void solve_triangular_super(double **matrix, int rows, int cols, double *x, double *y, int gap)
{
    /*Es de suma importancia recordar la transformacion que se hizo

    1 MATRIZ TRIANGULAR SUPERIOR
    queda desfasada un lugar a la derecha

    123
    045
    006     Ahora para hacer las mismas operaciones pensando
            en que no existe desface se debe de acceder

                        matrix[i][j-i]

                        si gap es 0 considera matriz normal
                        si gap es -1 considera matriz desfasada


    123
    450
    600
    */
    int i = ZERO;
    int n = rows-ONE;

    if(cols != rows)
    {
        printf("No se puede sollucionar, no es matriz cuadrada\n");
        x = NULL;
    }
    else
    {

        while(i < rows)
        {
            if(*(*(matrix + i)+ (gap?ZERO:i)) == 0)
            {
                printf("0 en diagonal no hay solucion\n");
                x = NULL;
            }

            i++;

        }

        /*el ultimo termino es rows-ONE*/
        *(x + n) = *(y + n)/ (*(*(matrix + n) + (gap?ZERO:n)));

        i = n - ONE;

        while(i >= 0)
        {

            *(x + i) =  ((*(y + i)) - sumatoria(matrix, x, i, rows, i + ONE, n, (gap?-i:ZERO))) / *(*(matrix+i) + (gap?ZERO:i));
            i--;
        }


    }
}
