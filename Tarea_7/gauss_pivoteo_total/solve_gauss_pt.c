#include <math.h>
#include <stdlib.h>

#include <stdio.h>
#define ZERO 0
#define ONE 1
#define TWO 2

double sumatoria_(double **matrix,  double *x, int i, \
  int n, int begin, int end)
{
    double sum = ZERO;
    int j = begin;

    while(j <= end)
    {
        sum += (*(*(matrix+i) + j)) * (*(x + j));
        j++;
    }

        return sum;
}

void solve_triangular_super_(double **matrix, int rows, double *x)
{

    int i = ZERO;
    int n = rows-ONE;

    /*el ultimo termino es rows-ONE*/
    *(x + n) = *(*(matrix + n) + rows)/ (*(*(matrix + n) + n));
    i = n - ONE;

    while(i >= 0)
    {
        *(x + i) =  (*(*(matrix + i) + rows)\
        - sumatoria_(matrix, x, i, rows, i + ONE, n))\
         / *(*(matrix+i) + i);
        i--;
    }



}


double maximo(double **matrix, int m, int i_o, int *i_c, int *j_c)
{
    /*funcion que encuentra el mayor valor absoluto dentro de un
    arreglo en dos dimensiones*/
    int j, i;
    double maxi;

    i = i_o;

    /*se considera como mayor el primer elemento
    de la submatriz*/
    maxi = fabs(*(*(matrix + i_o) + i_o));

    while(i < m)
    {

        j = i_o;

        while(j < m)
        {
            if(fabs(*(*(matrix + i) + j)) >= maxi)
            {
                *j_c = j;
                maxi = fabs( *(*(matrix + i) + j) );
                *i_c = i;
            }

            j++;
        }

        i++;
    }

    return maxi;
}

int pivoteo(double **matrix, int m,\
              int *signo, int *cambios_x)
{
    int i, i_c, j_c, l, j, k;
    double *temp_fila, aux, factor, val;

    for(i = ZERO; i < m; i++)
    {
        *(cambios_x + i) = i;
    }

    for(i = ZERO; i < m; i++)
    {
        i_c = i;
        j_c = i;
        /*encuentra las coordenadas del elemento mas grande*/
        val = maximo(matrix, m, i, &i_c, &j_c);

        if(val == 0.)
        {
            printf("Cero en la diagonal, sin solucion unica");
            return ZERO;
        }

        if((i != i_c && i == j_c) || (i == i_c && i != j_c))
        {
            /*se usara para calcular el determinante*/
            *signo *= -ONE;
        }

        if(i !=  i_c)
        {
            temp_fila = *(matrix + i);
            *(matrix + i) = *(matrix + i_c);
            *(matrix + i_c) = temp_fila;
        }

        if(i != j_c)
        {
            for(k = ZERO; k < m; k++)
            {
                aux = *(*(matrix + k) + j_c);
                *(*(matrix + k) + j_c) = *(*(matrix + k) + i);
                *(*(matrix + k) + i) = aux;

            }

            aux = *(cambios_x + i);
            *(cambios_x + i) = *(cambios_x + j_c);
            *(cambios_x + j_c) = aux;

        }

        for(l = i + ONE;  l < m; l++) /*se comienzan a hacer las columnas ceros*/
        {
            factor = *(*(matrix + l) + i) / *(*(matrix + i) + i);


            for(j = i; j < m+1; j++)
            {

                *(*(matrix + l) + j) -= factor * (*(*(matrix + i) + j));

            }

        }

    }

    return ONE;

}

int gauss(double **matrix, int m, double *x, double *y, int *signo)
{
    int i, j, k, su;
    int cambios_x[m];
    double aux, aux_i;

    /*matriz aumentada*/
    for(i = ZERO; i < m; i++)
        matrix[i][m] = *(y+i);

    su = pivoteo(matrix, m, signo, cambios_x);

    if(su)
    {
        solve_triangular_super_(matrix, m, x);

        /*regresa x a sus pocision original*/
        for(i = ZERO; i < m; i++)
        {
            for(j = ZERO; j < m; j++)
            {
                if(*(cambios_x + j) == i)
                    k = j;
            }

            aux = *(x + k);
            *(x + k) = *(x + i);
            *(x + i)  = aux;

            aux_i = *(cambios_x + k);
            *(cambios_x + k) = *(cambios_x + i);
            *(cambios_x + i) = aux_i;
        }

        return ONE;

    }
    else
        return ZERO;

}
