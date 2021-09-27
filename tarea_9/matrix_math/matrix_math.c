#include <stdlib.h>
#ifndef ZERO
#define ZERO 0
#endif /*ZERO*/

#ifndef ONE
#define ONE 1
#endif /*ONE*/

#ifndef TWO
#define TWO 2
#endif /*TWO*/

void producto_escalar(double a, double *x, int m)
{
    /*Funcion que multiplica un escalar a un vector
    el resultado se guarda en el vector x*/

    int i;

    for(i = ZERO; i < m; i++)
        *(x + i) *= a;
}


void vector_sum(double *x, double *y, int m)
{
    /*funcion que suma elemento a elemento dos vectores,
    el resultado se guardo en el vector x*/

    int i;

    for(i = ZERO; i < m; i++)
    {
        *(x + i) += *(y + i);
    }

}

void vector_rest(double *x, double *y, int m)
{
    /*funcion que resta elemento a elemento dos vectores,
    el resultado se guardo en el vector x*/

    int i;

    for(i = ZERO; i < m; i++)
    {
        *(x + i) -= *(y + i);
    }

}

void normalizar_vector(double *vector, int m)
{
    /*funcion que normaliza un vector*/

    int i;
    double suma = ZERO;

    /*calcula el denominador*/
    for(i = ZERO; i < m; i++)
    {
        suma += (*(vector + i)) * (*(vector + i));
    }

    for(i = ZERO; i < m; i++)
    {
        *(vector + i) /= suma;
    }

}

double dot_vector(double *a, double *b, int m)
{
    /*Realiza el producto punto entre dos vectores*/

    int i;
    double suma = ZERO;

    for(i = ZERO; i < m; i++)
    {
        suma += (*(a + i)) * (*(b + i));
    }

    return suma;
}

double *dot(double **a, double *b, int m, int n)
{
    /*funcion que realiza el producto punto entre una
    matriz y un vector
    double **a: es la matriz a
    double **b: es la matriz b
    int m: es el numero de filas de la matriz a
    int n: es el numero de columnas de la matriz a y corresponde al
    numero de filas del vector b*/

    double suma;
    int i, j;
    double *result = (double *)calloc(m, sizeof(double));

    for(i = ZERO; i < m; i++)
    {
        suma = ZERO;

        for(j = ZERO; j < n; j++)
        {
            suma += (*(*(a +  i) + j)) * (*(b + j));

        }

         *(result + i) = suma;
    }

    return result;
}
