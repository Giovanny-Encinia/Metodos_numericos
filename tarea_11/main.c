#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_math/matrix_math.h"
#include "rayleigh/rayleigh.h"
#include "print_read/prdynamic.h"
#include "subespacio/subespacio.h"
#ifndef ZERO
#define ZERO 0
#endif/*ZERO*/
#define NU 3

void print_ray(char *name, char *save, double *eigenvector, double eigenvalor)
{
    double **matrix;
    int i, m, n;
    FILE *file;

    file = fopen(save, "w");

    matrix = read_matrix_file(name, &m, &n, ZERO);
    printf("\nMetodo de Rayleigh\n");
    printf("===================================================\n");
    rayleigh_eigen(matrix, m, &eigenvalor, eigenvector);
    fprintf(file, "El eigenvalor es: %lf\n", eigenvalor);
    fprintf(file, "El eigenvector es:\n");

    for(i = ZERO; i < m; i++)
        fprintf(file, "%.10lf, ", *(eigenvector + i));

    printf("Se ha guardado el resultado en : %s\n", save);

    printf("===================================================\n");
    free_matrix(matrix, m);
    fclose(file);
}

void print_subes(char *name, char *save, int number_eigen)
{
    int i, m, n, j;
    double **eigenvectores, **eigenvalores, **matrix;
    FILE *file;

    file = fopen(save, "w");

    eigenvalores = (double **)malloc(number_eigen * sizeof(double *));
    *eigenvalores = (double *)malloc(number_eigen * number_eigen * sizeof(double));

    for (i = ONE; i < number_eigen; i++)
        *(eigenvalores + i) = *(eigenvalores + i - ONE) + number_eigen;

    matrix = read_matrix_file(name, &m, &n, ZERO);

    printf("\nMetodo del Subespacio\n");
    printf("===================================================\n");
    eigenvectores = subespacio(matrix, m, number_eigen, eigenvalores);
    fprintf(file, "Los eigenvalores son:\n\n");

    for (j = ZERO; j < number_eigen; j++)
        fprintf(file, "%.10lf, ",*(*(eigenvalores + j) + j));

    fprintf(file, "\n\nLos eigenvectores(en columnas) son:\n\n");

    for (i = ZERO; i < m; i++)
    {
        for (j = ZERO; j < number_eigen; j++)
            fprintf(file, "%.10lf, ", *(*(eigenvectores + i) + j));

        fprintf(file, "\n");
    }

    printf("Se ha guardado el resultado en : %s\n", save);
    printf("\n===================================================\n");

    free(eigenvalores[0]);
    free(eigenvalores);
    free_matrix(eigenvectores, number_eigen);
    free_matrix(matrix, m);
    fclose(file);
}

int main(void)
{
    double eigenvalor, eigenvector1[3];
    double eigenvalor2 = 9;
    double eigenvector2[] = {
        -0.1,
        0.008510,
        0.001980,
        0.002672,
        0.002070,
        0.001903,
        0.000312,
        0.000465,
        0.000954,
        0.000307,
        0.000556,
        0.000430,
        0.000536,
        0.000292,
        0.000394,
        0.000643,
        0.000593,
        0.000397,
        0.000391,
        0.000068,
        0.000296,
        0.000001,
        0.000104,
        0.000054,
        0.000331,
        0.000057,
        0.000148,
        0.000042,
        0.000033,
        0.000341,
        0.000067,
        0.000161,
        0.000259,
        0.000181,
        0.000084,
        0.000179,
        0.000141,
        0.000129,
        0.000252,
        0.000092,
        0.000189,
        0.000126,
        0.000180,
        0.000089,
        0.000299,
        0.000069,
        0.000073,
        0.000169,
        0.000198,
        0.000011,
    };

    eigenvalor = 10.7;
    eigenvector1[0] = -0.029;
    eigenvector1[1] = -0.098;
    eigenvector1[2] = 1.01;


    print_ray("Materiales/Eigen_3x3.txt", "Resultados/ra/3x3.txt", eigenvector1, eigenvalor);
    print_ray("Materiales/Eigen_50x50.txt", "Resultados/ra/50x50.txt", eigenvector2, eigenvalor2);
    print_subes("Materiales/Eigen_125x125.txt", "Resultados/sub/125.txt", 6);
    print_subes("Materiales/Eigen_500x500.txt", "Resultados/sub/500.txt", 25);

    return ZERO;
}