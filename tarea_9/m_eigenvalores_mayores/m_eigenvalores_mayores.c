#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../print_read/prdynamic.h"
#include "../matrix_math/matrix_math.h"
#ifndef ZERO
#define ZERO 0
#endif /*ZERO*/

#ifndef ONE
#define ONE 1
#endif /*ONE*/

#ifndef TWO
#define TWO 2
#endif /*TWO*/
#define LIMIT 1000000
#define ERROR 1E-12

double *eigen_mayores(char *name, int *m_c, int number)
{
    /*Calcula el eigenvalor y eigen vector dominante de
    una matriz

    Parametros
    ===========
    char *name: el nombre del archivo de donde se leera la matriz
    int *m_c: variable en donde se alojara el tamanio de la matriz
    */

    double **matrix, *x1, *x0, lambda_old = ZERO;
    double xnv0, *xn;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    double *sol, *contribution;
    int condition = ONE;
    int  n, iteration = ZERO, m, i, j;

    matrix = read_matrix_file(name, &m, &n, ZERO);
    *m_c = m;
    /*aqui se guardan los eigenvalores*/
    sol = (double *)malloc(m * sizeof(double));
    contribution = (double *)calloc(m, sizeof(double));

    /*Se crea espacio para el vector inicial*/
    x0 = (double *)calloc(m, sizeof(double));
    xn = (double *)calloc(m, sizeof(double));

    for(j = ZERO; j < m; j++)
        *(x0 + j) = ONE / sqrt(n);

    for(i = ZERO; i < number; i++)
    {

    lambda_old = ZERO;


    while(condition && iteration < LIMIT)
    {



        /*calcula el valor del nuevo vector con Ax0 = x1*/
        x1 = dot(matrix, x0, m, m);

        /*calcula el valor de lambda x1^{T}x0/ x0^{T}x0*/
        *(sol + i) = dot_vector(x1, x0, m) / dot_vector(x0, x0, m);

        /*identifica cuando converge al eigenvalor dominante*/
        if(fabs(lambda_old - (*(sol + i))) < ERROR)
        {
            /*se guarda el eigenvector dominante*/
            for(j = ZERO; j < m; j++)
                *(xn + j) = *(x1 + j);

            free(x1);
            print_array(xn, m);
            break;
        }

        lambda_old = *(sol + i);


        for(j = ZERO; j < m; j++)
            *(x0 + j) = *(x1 + j);

        free(x1);
        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/
        normalizar_vector(x0, m);

        if(i)
        {
            /*\hat{v_{0}} = v0 - xn *v0 *xn */
            xnv0 = dot_vector(xn, x0, m);
            producto_escalar(xnv0, xn, m);
            vector_sum(contribution, xn, m);
            vector_rest(x0, contribution, m);

        }



    }

    }

    free(xn);
    free(x0);
    free(contribution);
    free_matrix(matrix, m);

    return sol;
}
