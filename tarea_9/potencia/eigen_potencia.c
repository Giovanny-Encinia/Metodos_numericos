#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../print_read/prdynamic.h"
#define ZERO 0
#define ONE 1
#define TWO 2
#define LIMIT 1000000
#define ERROR 1E-8

void free_solution_eigen(double **solution)
{
    free(*(solution));
    free(*(solution + ONE));
    free(solution);
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

double **eigen_dominante(char *name, int *m_c)
{
    double **matrix, *x1, *x0, lambda_old = ZERO;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    double **sol = (double **)malloc(TWO * sizeof(double *));
    int condition = ONE;
    int  n, iteration, m;

    matrix = read_matrix_file(name, &m, &n, ZERO);
    *m_c = m;
    *sol = (double*)malloc(sizeof(double));
    *(sol + ONE) = (double*)malloc(m * sizeof(double));
    /*Se crea espacio para el vector inicial*/
    x0 = (double*)calloc(m, sizeof(double));

    *x0 = ONE / sqrt(n);

    while(condition || iteration > LIMIT)
    {
        /*calcula el valor del nuevo vector con Ax0 = x1*/
        x1 = dot(matrix, x0, m, m);
        /*calcula el valor de lambda x1^{T}x0/ x0^{T}x0*/
        **(sol) = dot_vector(x1, x0, m) / dot_vector(x0, x0, m);

        /*identifica cuando converge al eigenvalor dominante*/
        if(fabs(lambda_old - (**sol)) < ERROR)
        {
            /*se guarda el eigenvector*/
            *(sol + ONE) = x1;
            printf("El numero de iteraciones es: %d\n", iteration);
            return sol;
        }

        lambda_old = **(sol);
        x0 = x1;
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
