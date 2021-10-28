#include <stdlib.h>
#include <stdio.h>
#include "../matrix_math/matrix_math.h"
#include "../print_read/print_read.h"

double **qr_factor(double **matrix, int m)
{
    /*funcion que realiza un factorizacion tipo QR
    
    Parametros
    ===========
    
    double **matrix: es una matriz en  donde se puede acceder
    a sus vectores columnas facilmente, se tiene pensado que 
    la matriz este de una foma traspuesta para poder hacer las
    operaciones facilmente
    
    int m: es una variable que indica la dimension de la matriz
    
    Return
    ========

    double **r: la matriz R que es una matriz triangular superior
    */

    double **q, **r, *sumatoria;
    int i, j, k;

    /*crea una nueva matriz r que contendra la matriz
    triangular superior*/
    r = matrix_zero(m, m);
    /*matriz que contendra a la matriz Q*/
    q = copy_matrix(matrix, m, m);

    /*debemos recordar que matrix es una traspuesta y que q 
    debe de mantener la misma forma, es decir los vectores
    se encuentran en las filas*/
    for(i = ZERO; i < m; i++)
        *(*(q) + i) = *(*(matrix) + i);

    /*parte de la teoria indica que debemos normalizar*/
    normalizar_vector(*(q), m);
    /*se calcula el primer elemento de r*/
    **r = norma(*matrix, m);

    for(i = ONE; i < m; i++)
    {   
        sumatoria = (double *)calloc(m, sizeof(double));

        /*se calculan lor elementos de la mtriz r
        a la vez se calcula el termino de sumatoria para a* */
        for(j = ZERO; j <= i - ONE; j++)
        {

            if(j < i)
                *(*(r + j) + i) = \
                dot_vector((*(q + j)), (*(matrix + i)), m);

            for(k = ZERO; k < m; k++)
                *(sumatoria + k) += (*(*(r + j) + i))\
                 * (*(*(q + j) + k));

        }

        /*esto en las notas es ai* */
        vector_rest(*(q + i), sumatoria, m);
        /*se calcula la norma si los indices son iguales*/
        *(*(r + i) + i) = norma(*(q + i), m);
        free(sumatoria);
        /*se normaliza el nuevo vector de Q*/
        normalizar_vector(*(q + i), m);
    }

    for(i = ZERO; i < m; i++)
    {

        for(j = ZERO; j < m; j++)
        {
            /*se copian los valores de Q a la matriz original
            de tal manera que los vectores renglo de Q traspuesta
            seran los vectores columna, es decir de vuelve
            a trasponer*/
            *(*(matrix + i) + j) = *(*(q + j) + i); 
        }

    }

    return r;
}