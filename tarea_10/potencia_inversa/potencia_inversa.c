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
#define DELTA 0.0001
void free_solution_eigen_(double **solution)
{
    free(*(solution));
    free(*(solution + ONE));
    free(solution);
}

double **eigen_menor(double **matrix, int m, double **eigen_old , int k)
{
    /*Calcula el eigenvalor y eigen vector menor de
    una matriz

    Parametros
    ===========
    char *name: el nombre del archivo de donde se leera la matriz
    int *m_c: variable en donde se alojara el tamanio de la matriz
    */
    /*lambda_old al inicio tiene un valor muy grande*/
    char a[] = "jola";
    /*double eigen_old[] = {0.999191, 0.027147, 0.029675};*/
    double ai;
    double *x1, *x0, lambda_old = 400000000;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    /*sol es una matriz que contiene los eigen pares*/
    double **sol = (double **)malloc(TWO * sizeof(double *));
    double numerador, denominador;
    int condition = ONE;
    int iteration = ZERO, value, i, j;

    /*el primer elemento de la matriz sol contiene el eigenvalor*/
    *sol = (double*)malloc(sizeof(double));
    *(sol + ONE) = (double*)malloc(m * sizeof(double));
    /*Se crea espacio para el vector inicial*/
    x0 = (double*)calloc(m, sizeof(double));

    /*se inicializa el primer vector, el cual es un vector normalizado*/


    if(k > ZERO)
    {
        /*el vector cero sera el eigenvector
        anterior y le agregaremos un incremento pequenio
        esto para evitar que algun denominador en el calculo
        del eigenvalor sea cero*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = (*(*(eigen_old + k) + i)) + DELTA;
    }
    else
    {
        /*el primer vectopr inicial del primer eigenvalor(el menor)
        se inicializa como 1/sqrt(m)*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = ONE/sqrt(m);
    }


    while(condition && iteration < LIMIT)
    {

        /*aqui se quitan los terminos anteriores
        de los eigenvectores*/
        for(i = ZERO; i < k; i++)
        {
            /*es el producto punto de el eigenvector traspuesto
            y el x0*/
            ai = dot_vector(*(eigen_old + ++i), x0, m);

            /*a cada elemento del vactor se le resta an*eigen_valor_{i}*/
            for(j = ZERO; j < m; j++)
                *(x0 + j) -= ai * (*(*(eigen_old + i) + j));

        }


        /*calcula el valor del nuevo vector con x0 = A^{-1}x1*/
        x1 = (double *)calloc(m, sizeof(double));
        /*el nuevo vector es x1 y value se usa para saber si se realizo
        correctamente la factorizacion*/

        value = solve_lu(matrix, m, x1, x0, iteration);


        if(!value)
            printf("No se puede factorizar\n");

        /*calcula el valor de lambda x1^{T}x0/ x0^{T}x0*/
        numerador = dot_vector(x0, x0, m);
        denominador = dot_vector(x1, x0, m);

        /*es el nuevo valor del eigenvalor*/
        **(sol) = numerador / denominador;

        /*identifica cuando converge al eigenvalor dominante*/
        if(fabs(lambda_old - (**sol)) < ERROR)
        {
            /*se guarda el eigenvector*/
            /*memoria en x1 se elimina al eliminar memoria de sol*/
            normalizar_vector(x1, m);
            *(sol + ONE) = x1;
            printf("\tIteraciones: %d\n", iteration);
            /*liberamos la memoria de x0*/
            free(x0);
            /*liberamos la matriz que se aha creado*/

            return sol;
        }

        /*se actualiza lammbda old*/

        lambda_old = **(sol);

        /*se actualiza el vector inicial*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = *(x1 + i);

        normalizar_vector(x0, m);

        free(x1);
        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/
        iteration++;
    }

    free(x0);
    printf("No se puede encontrar la solucion\n");

    return NULL;
}

int eigen_menores(char *name, int *m_c)
{
    int m, n, i, j;
    double **matrix = read_matrix_file(name, &m, &n, ZERO);
    double **sol, **eigen_old;

    *m_c = m;

    eigen_old = (double **)malloc((m + 1) * sizeof(double *));

    for(i = ZERO; i < 2; i++)
    {

    sol = eigen_menor(matrix, m, eigen_old, i);
    printf("\t|Eigen Menor%71s\n", "|");
    printf("\t------------------------");
    printf("-----------------------------------------------------------\n");
    printf("\tEigenvalor: %lf\n", **sol);
    printf("\tEigenvalor\n");
    print_solucion(*(sol + ONE), m);

    *(eigen_old + i + ONE) = (double *)malloc(m * sizeof(double));

    for(j = ZERO; j < m; j++)
       *(*(eigen_old + i + ONE) + j) =  *(*(sol + ONE) + j);

    printf("\t========================");
    printf("===========================================================\n");
    printf("\n");
    free_solution_eigen_(sol);
    }

    free_matrix(matrix, m);
    free_expanded_matrix(eigen_old, m);


    return ONE;
}