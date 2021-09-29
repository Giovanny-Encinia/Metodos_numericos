#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../print_read/prdynamic.h"
#include "../matrix_math/matrix_math.h"
#include "../LU/factorization_lu.h"
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
#define ERROR 1E-13

void free_solution_eigen_(double **solution)
{
    free(*(solution));
    free(*(solution + ONE));
    free(solution);
}

double **eigen_menor(char *name, int *m_c)
{
    /*Calcula el eigenvalor y eigen vector menor de
    una matriz

    Parametros
    ===========
    char *name: el nombre del archivo de donde se leera la matriz
    int *m_c: variable en donde se alojara el tamanio de la matriz
    */

    double **matrix, *x1, *x0, lambda_old = 400000000;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    double **sol = (double **)malloc(TWO * sizeof(double *));
    int condition = ONE;
    int  n, iteration = ZERO, m, value, i;

    x1 = (double *)calloc(m, sizeof(double));
    matrix = read_matrix_file(name, &m, &n, ZERO);
    *m_c = m;
    *sol = (double*)malloc(sizeof(double));
    *(sol + ONE) = (double*)malloc(m * sizeof(double));
    /*Se crea espacio para el vector inicial*/
    x0 = (double*)calloc(m, sizeof(double));

    *x0 = ONE/sqrt(m);

    while(condition && iteration < LIMIT)
    {
        /*calcula el valor del nuevo vector con x0 = A^{-1}x1*/
        value = solve_lu(matrix, m, x1, x0, iteration);

        if(!value)
            printf("No se puede factorizar\n");

        /*calcula el valor de lambda x1^{T}x0/ x0^{T}x0*/
        **(sol) = dot_vector(x0, x0, m) / dot_vector(x1, x0, m);

        /*identifica cuando converge al eigenvalor dominante*/
        if(fabs(lambda_old - (**sol)) < ERROR)
        {
            /*se guarda el eigenvector*/
            /*memoria en x1 se elimina al eliminar memoria de sol*/
            *(sol + ONE) = x1;
            printf("\tIteraciones: %d\n", iteration);
            free(x0);
            free_matrix(matrix, m);
            return sol;
        }

        lambda_old = **(sol);

        for(i = ZERO; i < m; i++)
            *(x0 + i) = *(x1 + i);

        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/
        normalizar_vector(x0, m);
        iteration++;
    }

    free(x0);
    free_matrix(matrix, m);

    return sol;
}
