#include <stdio.h>
#include <stdlib.h>
#define ZERO 0
#define ONE 1
#define TWO 2

double sum_cholesky(double **cholesky_mat, int m, int i, int j)
{
    /*Aqui se calculan las sumatorias de las ecuaciones de los elementos de la
    matriz diagonal y de la matriz triangular

    Los datos de entrada deben de ser
    cholesky_mat: la ,atriz donde se guardara la informacion de la factorizacion
    m: las filas de la matriz
    i: numero que hace referencia a la i-esima fila
    j: numero que hace referencia a la j-esima fila

    regresa suma
    */
    int k;
    double suma = ZERO;

    if(i == j)
    {

        for(k = ZERO; k <= i - ONE; k++)
        {
            suma += (*(*(cholesky_mat + i) + k)) * (*(*(cholesky_mat +i) + k)) * (*(*(cholesky_mat + k) + k));
        }

    }
    else
    {

        for(k = ZERO; k <= j - ONE; k++)
        {
            suma += (*(*(cholesky_mat + i) + k)) * (*(*(cholesky_mat +j) + k)) * (*(*(cholesky_mat + k) + k));
        }

    }

    return suma;

}

void cholesky_value(double **cholesky_mat, int m, int i, int j, double (*f)(int, int))
{
    /*Calcula el valor que  se pondra en la matriz con la informacion de la
    factorizacion, depende mucho de si lo que se pasa ha sido una funcion
    generadora o son a partir de la lectura de algun archivo*/

    if(f != NULL)
    {

        if(i == j)
        {

            *(*(cholesky_mat + i) + i) = f(i, i) - sum_cholesky(cholesky_mat, m, i, j);
        }
        else
             *(*(cholesky_mat + i) + j) = (f(i, j) - sum_cholesky(cholesky_mat, m, i, j)) / *(*(cholesky_mat + j) + j);

    }
    else
    {

        if(i == j)
            *(*(cholesky_mat + i) + i) -= sum_cholesky(cholesky_mat, m, i, j);
        else
             *(*(cholesky_mat + i) + j) = (*(*(cholesky_mat + i) + j) - sum_cholesky(cholesky_mat, m, i, j)) / *(*(cholesky_mat + j) + j);

    }


}

double **create_space_cholesky(int rows)
{
    /*
    Crea un arreglo unidimensional que emula una matriz en 2d, es mas rapido
    acceder a los elementos.
    ===========================================================

    MATRIZ TRIANGULAR INFERIOR
    La matriz se accede de la misma manera que siempre, pero
    hay que considerar que no se puede acceder a los intervalos
    de los ceros, ya que no se asigno memoria a los 0's

    retornara una matriz inferior
    ==============================================================

    */

    int i = ONE, m, n, factor = 0;
    double **matrix = (double**)malloc(rows * sizeof(double*));

    m = n = rows;

    if(matrix == NULL)
    {
        printf("Memory full");

        return NULL;
    }


    factor = (m * n - (m * (m - ONE))/TWO);

    *(matrix) = (double*)malloc(factor * sizeof(double));

    /*divide in blocks , analogue to rows*/
    while(i < m)
    {
        *(matrix + i) = *(matrix + i - ONE) + i;
        i++;
    }

    return matrix;
}

void cholesky(double **matrix, int rows, double (*f)(int, int))
{
    /*Solamente se considera que la matriz puede ser repreentanda mediante
    una triangular inferior, no tomo en cuenta matrices bandadas por el momento
    matrix es un arrglo doble que se tuvo que haber leido previamente como una matriz
    triangular inferior*/

    double **cholesky_mat;
    int i, j, k;

    cholesky_mat = matrix;

    /*se crea una estructuta para poder almacenar
    si solo se tiene una funcion generadora*/
    if(f != NULL)
    {

        **cholesky_mat = f(ZERO, ZERO);

        for(k = ONE; k < rows; k++)
            *(*(cholesky_mat + k)) = f(k, ZERO) / (**cholesky_mat);

    }
    else
    {

        for(k = ONE; k < rows; k++)
            *(*(cholesky_mat + k)) = *(*(cholesky_mat + k)) / (**cholesky_mat);

    }


     i = ONE;

    /*Read and save the data in dynamic memory*/
    while(i < rows)
    {

        j = ONE;

        /*Al ser una matriz triangular se puede ver simplemente
        como una matriz triangular inferior*/

        while(j <= i)
        {
            /*se comienza a llenar los valores faltantes*/
            cholesky_value(cholesky_mat, rows, i, j, f);
            j++;
        }

        i++;
    }

}
