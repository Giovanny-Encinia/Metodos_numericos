#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../print_read/prdynamic.h"
#include "../matrix_math/matrix_math.h"
#include "../potencia/eigen_potencia.h"
#ifndef ZERO
#define ZERO 0
#endif /*ZERO*/

#ifndef ONE
#define ONE 1
#endif /*ONE*/

#ifndef TWO
#define TWO 2
#endif /*TWO*/
#define LIMIT 100000
#define ERROR 1E-12


double *eigen_n_mayor(double **matrix, int m, int it_k, double **xn)
{
    double *x1, *x0, lambda_old = ZERO, xnv0, *xn_c, *contribution, lambda;
    int i, condition = ONE, iteration = ZERO, j;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    contribution = (double *)calloc(m, sizeof(double));
    /*Se crea espacio para el vector inicial*/
    x0 = (double*)calloc(m, sizeof(double));
    xn_c = (double*)calloc(m, sizeof(double));

    for(i = ZERO; i < m; i++)
        *(x0 + i) = ONE / sqrt(m);

    while(condition && iteration < LIMIT)
    {

        /*calcula el valor del nuevo vector con Ax0 = x1*/
        x1 = dot(matrix, x0, m, m);
        /*calcula el valor de lambda x1^{T}x0/ x0^{T}x0*/
        lambda = dot_vector(x1, x0, m) / dot_vector(x0, x0, m);

        /*identifica cuando converge al eigenvalor dominante*/
        if(fabs(lambda_old - lambda) < ERROR)
        {
            /*se guarda el eigenvector*/
            normalizar_vector(x1, m);

            printf("\tEl numero de iteraciones es: %d\n", iteration);
            printf("Eigenvalor: %lf\n", lambda);
            free(x0);
            free(xn_c);
            free(contribution);
            return x1;
        }

        lambda_old = lambda;

        for(i = ZERO; i < m; i++)
            *(x0 + i) = *(x1 + i);

        normalizar_vector(x0, m);
        free(x1);
        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/

        for(j = ZERO; j < it_k; j++)
        {
            xnv0 = dot_vector(*(xn + j), x0, m);

            for(i = ZERO; i < m; i++)
                *(xn_c + i) = *(*(xn + j) + i);

            producto_escalar(xnv0, xn_c, m);

            for(i = ZERO; i < m; i++)
                *(contribution + i) = *(xn_c + i);

            /*vector_sum(contribution, xn_c, m);*/
            vector_rest(x0, contribution, m);
        }

        iteration++;
    }

    free(contribution);
    free(xn_c);
    free(x0);

    printf("no hay solucion\n");
    return NULL;
}

void eigen_mayores(char *name, int *m_c, int number)
{
    /*Calcula el eigenvalor y eigen vector dominante de
    una matriz

    Parametros
    ===========
    char *name: el nombre del archivo de donde se leera la matriz
    int *m_c: variable en donde se alojara el tamanio de la matriz
    */

    double **sol, *xn_temp;
    double **matrix;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    double **xn;
    int  n, m, i, filas, j;

    matrix = read_matrix_file(name, &m, &n, ZERO);
    *m_c = m;

    if(m > 6)
        filas = m - 6;
    else
        filas = 2;

    xn = (double **)malloc(filas * sizeof(double *));

    for(i = ZERO; i < filas; i++)
        *(xn + i) = (double *)malloc(m * sizeof(double));

    sol = eigen_dominante(name, &m);

    for(i = ZERO; i < m; i++)
        *(*xn + i) = *(*(sol + ONE) + i);

    for(i = ONE; i < filas; i++)
    {
        xn_temp = eigen_n_mayor(matrix, m, i, xn);

        for(j = ZERO; j < m; j++)
            *(*(xn + i) + j) = *(xn_temp + i);

        print_solucion(xn_temp, m);

    }


    free(xn_temp);
    free_solution_eigen(sol);
    free_matrix(matrix, m);

}
