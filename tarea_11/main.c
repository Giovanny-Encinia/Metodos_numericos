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
    {
        fprintf(file, "%.10lf ", *(eigenvector + i));
        i++;

        if (i % 5 == ZERO)
            fprintf(file, "\n");

    }

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
}

int main(void)
{
    double eigenvalor, eigenvector1[3];
    double eigenvalor2 = 9;
    double eigenvector2[] = {
        -0.999955,
        0.008310,
        0.001880,
        0.002572,
        0.001970,
        0.001803,
        0.000302,
        0.000455,
        0.000944,
        0.000297,
        0.000546,
        0.000420,
        0.000516,
        0.000272,
        0.000354,
        0.000623,
        0.000563,
        0.000367,
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
        0.000072,
        0.000189,
        0.000126,
        0.000180,
        0.000089,
        0.000199,
        0.000059,
        0.000073,
        0.000169,
        0.000188,
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