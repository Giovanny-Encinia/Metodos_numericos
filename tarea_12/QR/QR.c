#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../matrix_math/matrix_math.h"
#include "../print_read/print_read.h"
#define ERROR 1E-9

int condicion_paro(double **q, int m)
{
    /*Funcion que revisa que una matriz se aproxime
    a una matriz identidad
    
    Parametros
    ==========
    double **q: la matriz en la que se aplicara la comparacion 
    con la matriz identidad
    
    int m: es la dimension de la matriz
    
    Return
    ======
    
    regresa un entero condition, 0 si no es una matriz identidad
    1 si se aproxima a una matriz identidad*/

    int i, j;

    for(i = ZERO; i < m; i++)
    {

        for(j = ZERO; j < m; j++)
        {

            if(i == j)
            {

                if(fabs(*(*(q + i) + j) - ONE) > ERROR)
                    return ZERO;

            }
            else
            {

                if (fabs(*(*(q + i) + j)) > ERROR)
                    return ZERO;

            }

        }/*end for para columnas*/

    }/*end for para filas*/

    return ONE;

}/*end function condicion_paro*/

void qr_factor(double **matrix, double **r, int m)
{
    /*funcion que realiza un factorizacion tipo QR

    Parametros
    ===========

    double **matrix: es una matriz en  donde se puede acceder
    a sus vectores columnas facilmente, se tiene pensado que
    la matriz este de una foma traspuesta para poder hacer las
    operaciones facilmente.

    double **r: la matriz R que es una matriz donde se guardara
    la matriz triangular superior. R

    int m: es una variable que indica la dimension de la matriz

    Return
    ========
    void
    */

    double **q, *sumatoria;
    int i, j, k;

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
            /*se van calculando las r_ji*/
            if(j < i)
                *(*(r + j) + i) = \
                dot_vector((*(q + j)), (*(matrix + i)), m);

            /*esta calculando el termino que es la sumatoria*/
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
    }/*end for, calcula columnas*/

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

}

double *qr_eigen(double **matrix, int m)
{
    /*Funcion que realiza el algoritmo QR para encontrar
    los eigenpares
    
    Parametros
    ==========
    double **matrix: es la matriz a la que se le buscan los
    eigenpares y al converger en esta se guardan los
    eigenvectores
    
    int m: es la dimension de la matriz
    
    Return
    ======
    double *eigenvalores: La matriz que contiene los eigenvalores
    en su diagonal*/

    double **r, **resultado, **matrix_t, **xk, **eigenvectors;
    double **eigenvectors_c, *eigenvalores;
    int i, j, iteration = ZERO;

    eigenvectors = matriz_identidad(m);
    /*se manipulan los vectores que estan como filas*/
    matrix_t = traspuesta(matrix, m, m);
    r = matrix_zero(m, m);
    eigenvalores = (double *)calloc(m, sizeof(double));
    
    /*inicia el proceso iterativo, recordemos que Qk
    en nuestro caso es matrix_t*/
    while(!condicion_paro(matrix_t, m) && iteration < 20)
    {
        /*calcula la aproximacion a la matriz diagonal que
        contiene los eigenvalores*/
        qr_factor(matrix_t, r, m);
        xk = dot_matrix(r, matrix_t, m, m, m, m);

        eigenvectors_c = dot_matrix(eigenvectors, matrix_t, m, m, m, m);
        free_matrix(eigenvectors, m);
        eigenvectors = copy_matrix(eigenvectors_c, m, m);
        free_matrix(eigenvectors_c, m);
        free_matrix(matrix_t, m);
        /*se transpone para manipulas las vectores
        como filas de la matriz facilmente*/
        matrix_t = traspuesta(xk, m, m);
        free_matrix(xk, m);
        iteration++;

    }

    for (i = ZERO; i < m; i++)
    {

        for (j = ZERO; j < m; j++)
        {
            /*se copian los valores de Q a la matriz original
            de tal manera que los vectores renglo de Q traspuesta
            seran los vectores columna, es decir de vuelve
            a trasponer*/
            *(*(matrix + i) + j) = *(*(eigenvectors + i) + j);
        }
    }

    printf("iteration: %d\n", iteration);
    free_matrix(r, m);

    for(i = ZERO; i < m; i++)
        *(eigenvalores + i) = *(*(matrix_t + i) + i);
    
    free_matrix(matrix_t, m);

    return eigenvalores;
}