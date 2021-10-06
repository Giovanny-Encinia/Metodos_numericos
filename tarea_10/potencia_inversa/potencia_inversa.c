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

    /*double eigen_old[] = {0.999191, 0.027147, 0.029675};*/
    double ai;
    double *x1, *x0, lambda_old = 4000000;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    /*sol es una matriz que contiene los eigen pares*/
    double **sol = (double **)malloc(TWO * sizeof(double *));
    double numerador, denominador;
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
            *(x0 + i) = (*(*(eigen_old + k) + i));
    }
    else
    {
        /*el primer vectopr inicial del primer eigenvalor(el menor)
        se inicializa como 1/sqrt(m)*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = ONE/sqrt(m);
    }

    x1 = (double *)calloc(m, sizeof(double));

    while(iteration < LIMIT)
    {

        /*aqui se quitan los terminos anteriores
        de los eigenvectores*/
        for(i = ONE; i <= k; i++)
        {
            /*es el producto punto de el eigenvector traspuesto
            y el x0*/
            ai = dot_vector(*(eigen_old + i), x0, m);

            /*a cada elemento del vactor se le resta an*eigen_valor_{i}*/
            for(j = ZERO; j < m; j++)
                *(x0 + j) -= (ai * (*(*(eigen_old + i) + j)));

        }


        /*calcula el valor del nuevo vector con x0 = A^{-1}x1*/

        /*el nuevo vector es x1 y value se usa para saber si se realizo
        correctamente la factorizacion*/

        /*el atributo iteration + k es de suma imporrtancia,
        cuando este es cero se factoriza LU y se gusrda en la matriz, cuando este es
        diferente de cero, ya no necesita factorizar y utiliza el LU encontrado por
        primera vez, en x1 se guarda el resultado*/
        value = solve_lu(matrix, m, x1, x0, iteration + k);


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

            for(i = ZERO; i < m; i++)
                *(*(sol + ONE) + i) = *(x1 + i);

            free(x1);
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

        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/
        iteration++;
    }

    free(x0);
    printf("No se puede encontrar la solucion\n");

    return NULL;
}

double **eigen_menores(char *name, int *number, double *eigen_valores, double **eigen_vectores, int m_eigen)
{

    int m, n, i, j, number_eigen;
    double **matrix = read_matrix_file(name, &m, &n, ZERO);
    double **sol, **eigen_old, *eigen_values;
    /*archivo Resultados/Materiales/....txt*/

    number_eigen = m_eigen;
    *number = number_eigen + ONE;
    /*se crea memoria para los eigenvectores*/
    /*el primer elemento de los eigenvectores
    sera el vector 0, asi que se debe tener cuidado*/
    eigen_old = (double **)malloc((number_eigen + ONE) * sizeof(double *));
    eigen_values = (double *)malloc((number_eigen + ONE) * sizeof(double));

    for(i = ZERO; i < number_eigen; i++)
    {

        sol = eigen_menor(matrix, m, eigen_old, i);




        if(m < 7)
        {
            printf("\t|Eigen Menor %5d %71s\n", i,"|");
            printf("\t------------------------");
            printf("-----------------------------------------------------------\n");
            /*posicion cero tiene un eigenvalor*/
            /*0 eigenvalor
            1  {1, 1, 1, 1,...m}*/
            printf("\tEigenvalor: %lf\n", **sol);
            printf("\t|Eigen Valor %5d %71s\n", i,"|");
            /*solucion uno corresponde a un eigenvector*/
            print_solucion(*(sol + ONE), m);
            printf("\t========================");
            printf("===========================================================\n");
            printf("\n");
        }
printf("sol %lf\n", **sol);
        *(eigen_values + i) = **sol;
        *(eigen_old + i + ONE) = (double *)malloc(m * sizeof(double));

        for(j = ZERO; j < m; j++)
           *(*(eigen_old + i + ONE) + j) =  *(*(sol + ONE) + j);


        free_solution_eigen_(sol);
    }

    for(i = ZERO; i < number_eigen; i++)
    {
        *(eigen_valores + i) = *(eigen_values + i);
    }


    free_matrix(matrix, m);
    free(eigen_values);

    return eigen_old;
}
