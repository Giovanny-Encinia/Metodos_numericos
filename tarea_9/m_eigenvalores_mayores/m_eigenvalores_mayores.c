#include <stdlib.h>
#include <string.h>
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
#define LIMIT 1000
#define ERROR 1E-11

double **eigen_dominante_m(double **matrix, int m, double **eigen_values, int final_, int normalizar_)
{
    double  *x1, *x0, lambda_old = ZERO, an;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    double **sol = (double **)malloc(TWO * m * sizeof(double *));
    int condition = ONE;
    int  n, iteration = ZERO, k, j;
    int i;


    *sol = (double*)malloc(sizeof(double));
    *(sol + ONE) = (double*)malloc(m * sizeof(double));
    /*Se crea espacio para el vector inicial*/
    x0 = (double*)calloc(m, sizeof(double));

    for(i = ZERO; i < m; i++)
        *(x0 + i) = ONE / sqrt(m);

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
           /* printf("\tIteraciones: %d\n", iteration);*/
            free(x0);

            return sol;
        }

         lambda_old = **(sol);

        /*el valor old sera ahora el valor x1*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = *(x1 + i);

        if(normalizar_)
            normalizar_vector(x0, m);

        /*quita las contribuciones de los vectores anteriores*/
        if(final_ != 0)
        {
            /*opera sobre cada xn que se ha encontrado, siendo xn cada uno de
            los eigenvectores*/
            for(i = ZERO; i < final_; i++)
            {
                /*se define como el productopunto*/
                an = dot_vector(x0, *(eigen_values +  i), m);

                for(j = ZERO; j < m; j++)
                    *(x0 + j) -= an * (*(*(eigen_values +  i) + j));
            }

        }

        free(x1);
        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/
        normalizar_vector(x0, m);
        iteration++;
    }

    free(x0);


    return NULL;
}

void eigen_m(char *name, int *m_c, int normalizar_)
{
    double **solucion, **matrix, **eigen_values;
    int m, n, i, number_eigen, j, nu;
    char *resul = "Resultados/";
    char bufer[100];
    strcat(strcpy(bufer, resul), name);
    printf("%s\n", bufer);
    FILE *file = fopen(bufer, "w");

    matrix = read_matrix_file(name, &m, &n, ZERO);
    *m_c = m;

    if(m > 6)
        nu = m - 4;
    else
        nu = 2;



    eigen_values = (double **)malloc(nu * sizeof(double *));


    for(i = ZERO; i < nu; i++)
        *(eigen_values + i) = (double *)calloc(m, sizeof(double));


    for(j = ZERO; j < nu; j++)
    {

        solucion = eigen_dominante_m(matrix, m, eigen_values, j, normalizar_);

        if(solucion == NULL)
        {
            fprintf(file, "sin siol\n");
        }
        else
        {
            fprintf(file, "\tEigenvalor: %lf\n", **solucion);
            fprintf(file, "\tEigenvector:\n");

        for(i = ZERO; i < m; i++)
            *(*(eigen_values + j) + i) = *(*(solucion + ONE) + i);

        free_solution_eigen(solucion);
        }

    fprintf(file, "\t");

    while(i < m)
    {
        fprintf(file, "x%d: %lf ", i, *(*(eigen_values + j) + i));
        i++;

        if(i % 5 == ZERO)
            fprintf(file, "\n\t");
    }

    fprintf(file, "\n");

    }

    for(i = ZERO; i < nu; i++)
        free(eigen_values[i]);


    free(eigen_values);

    fclose(file);


}
