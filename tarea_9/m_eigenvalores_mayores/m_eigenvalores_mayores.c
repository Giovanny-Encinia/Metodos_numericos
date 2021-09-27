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
#define LIMIT 1000000
#define ERROR 1E-12


double **eigen_n_mayor(double **matrix, int m, int it_k, double *xn, double *contribution, double **sol)
{
    double *x1, *x0, lambda_old = ZERO, xnv0, *xn_c;
    int i, condition = ONE, iteration = ZERO;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/

    /*Se crea espacio para el vector inicial*/
    x0 = (double*)calloc(m, sizeof(double));
    xn_c = (double*)calloc(m, sizeof(double));

    for(i = ZERO; i < m; i++)
        *(x0 + i) = ONE / sqrt(m);
printf("x0\n");
print_array(x0, m);

    if(it_k)
    {
        /*\hat{v_{0}} = v0 - xn *v0 *xn */
        xnv0 = dot_vector(xn, x0, m);

        printf("p esc %.9lf\n", xnv0);
        for(i = ZERO; i < m; i++)
            *(xn_c + i) = *(xn + i);

        producto_escalar(xnv0, xn_c, m);
        printf("producto escalar\n");
        print_array(xn_c, m);
        vector_sum(contribution, xn_c, m);
        printf("contri\n");
print_array(contribution, m);
        vector_rest(x0, contribution, m);
        printf("new x0\n");
        print_array(x0, m);


    }

    while(condition && iteration < LIMIT)
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
            normalizar_vector(*(sol + ONE), m);
            printf("El numero de iteraciones es: %d\n", iteration);
            free(x0);
            free(xn_c);
            return sol;
        }

        lambda_old = **(sol);
        for(i = ZERO; i < m; i++)
            *(x0 + i) = *(x1 + i);

        normalizar_vector(x0, m);
        free(x1);
        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/


        if(it_k)
        {
            printf("x0\n");
print_array(x0, m);
        /*\hat{v_{0}} = v0 - xn *v0 *xn */
        xnv0 = dot_vector(xn, x0, m);

        printf("p esc %.9lf\n", xnv0);
        print_array(xn, m);

        for(i = ZERO; i < m; i++)
            *(xn_c + i) = *(xn + i);

        producto_escalar(xnv0, xn_c, m);
        printf("producto escalar\n");
        print_array(xn_c, m);
        vector_sum(contribution, xn_c, m);
        printf("contri\n");
print_array(contribution, m);
        vector_rest(x0, contribution, m);
        printf("new x0\n");
        print_array(x0, m);

        }


        iteration++;
    }

    free(xn_c);
    free(x0);

    return sol;
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

    double **sol = (double **)malloc(TWO * sizeof(double *));
    double **matrix;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    double *contribution;
    int  n, m, i;

    matrix = read_matrix_file(name, &m, &n, ZERO);
    *m_c = m;
    *sol = (double*)malloc(sizeof(double));
    *(sol + ONE) = (double*)malloc(m * sizeof(double));
    /*aqui se guardan los eigenvalores*/
    contribution = (double *)calloc(m, sizeof(double));

    /*Se crea espacio para el vector inicial*/

    sol = eigen_n_mayor(matrix, m, ZERO, NULL, contribution, sol);
    printf("El eigenvalor dominante es: %lf\n", **sol);
printf("nate\n");
        print_array(*(sol + ONE), m);
    for(i = ONE; i < 2; i++)
    {
        sol = eigen_n_mayor(matrix, m, i, *(sol + ONE), contribution, sol);
        printf("El eigenvalor dominante es: %lf\n", **sol);
         print_array(*(sol + ONE), m);


    }


    free_solution_eigen(sol);

    free(contribution);
    free_matrix(matrix, m);

}
