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
#define TAMANIO 2000

double **matrix_examen(void)
{
    /*Esta funcion sirve para crear la matriz del problema 4*/

    int i, j, k;
    double **matrix;
    double valores[] = {-4, -8, 40, -8, -4};

    matrix = (double **)calloc(TAMANIO , sizeof(double *));
    *matrix = (double *)calloc(TAMANIO * TAMANIO, sizeof(double ));

    for(i = 1; i < TAMANIO; i++)
    {
        *(matrix + i) = *(matrix + i - 1) + TAMANIO;
    }

    **matrix = 40;
    *(*matrix  + 1) = -8;
    *(*matrix  + 2) = -4;

    *(*(matrix + 1)) = -8;
    *(*(matrix + 1) + 1) = 40;
    *(*(matrix + 1) + 2) = -8;
    *(*(matrix + 1) + 3) = -4;

    for(i = 2; i < TAMANIO; i++)
    {
        k = 0;

        for(j = i - 2; j < TAMANIO; j++)
        {

            if(j >= 0 && k < 5)
            {
                *(*(matrix + i) + j) = *(valores + k++);
            }

        }

    }

    return matrix;

}

void imprime_examen(double **matrix)
{
    FILE *file;
 /*   file = fopen("Resultado/problema_4_eigenvectores.txt");
    fclose(file);*/

    int i, j;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 10; j++)
        {
            printf("%lf ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

}

void print_test(char *name, char *save, int number_eigen, int menores)
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
    eigenvectores = subespacio(matrix, m, number_eigen, eigenvalores, menores);
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

void print_subes(double **matrix, char *save, int number_eigen, int menores)
{
    int i, m = TAMANIO, n = TAMANIO, j;
    double **eigenvectores, **eigenvalores;
    FILE *file, *file_2;

    file = fopen(save, "w");
    if(menores)
        file_2 = fopen("Resultados/eigenvalores_menores.mtx", "w");
    else
        file_2 = fopen("Resultados/eigenvalores_mayores.mtx", "w");

    eigenvalores = (double **)malloc(number_eigen * sizeof(double *));
    *eigenvalores = (double *)malloc(number_eigen * number_eigen * sizeof(double));

    for (i = ONE; i < number_eigen; i++)
        *(eigenvalores + i) = *(eigenvalores + i - ONE) + number_eigen;

    printf("\nMetodo del Subespacio\n");
    printf("===================================================\n");
    eigenvectores = subespacio(matrix, m, number_eigen, eigenvalores, menores);
    fprintf(file_2, "10 1\n");

    for (j = ZERO; j < number_eigen; j++)
        fprintf(file_2, "%.10lf\n",*(*(eigenvalores + j) + j));

    fprintf(file, "2000 2000\n");

    for (i = ZERO; i < m; i++)
    {
        for (j = ZERO; j < number_eigen; j++)
            fprintf(file, "%.14lf ", *(*(eigenvectores + i) + j));

        fprintf(file, "\n");
    }

    printf("Se ha guardado el resultado en : %s\n", save);
    printf("\n===================================================\n");

    free(eigenvalores[0]);
    free(eigenvalores);
    free_matrix(eigenvectores, number_eigen);
    free_matrix(matrix, m);
    fclose(file);
    fclose(file_2);
}

void imprimir_jacobi(double **matrix, char *name_save, int tamanio)
{
    /*Lee una matriz en txt y retorna una matriz creada dinamicamente*/

    int m=2000, n=2000, i, j;
    char bufer[100];
    char bufer2[100];
    double **eigenvectores;
    FILE *file, *file_s;

    strcat(strcpy(bufer, name_save), "eigen_valores.txt");
    strcat(strcpy(bufer2, name_save), "eigen_vectores.txt");
    printf("%s\n", bufer2);
    /*la matriz se guarda como un vector, pero se
    puede acceder de manera estandar a cada uno de sus elementos*/

    /*ademas de que regresa la matriz con eigenvectores
    la variable matrix debe de contener en su diagonal los
    eigenvalores*/
    printf("\n\n\n======================================\n");
    printf("Metodo de Jacobi eigenpares\n");
    printf("======================================\n");
    eigenvectores = eigen_jacobi(matrix, m);
    if(tamanio < 4)
    {
        printf("\nLos eigenvalores en la diagonal son\n");
        printf("----------------------------------------\n");
        print_matrix(matrix, m, m);
        printf("\n\n");
        printf("Los eigenvectores en columnas son\n");
        printf("----------------------------------------\n");
        print_matrix(eigenvectores, m, m);
        printf("----------------------------------------\n");
    }

    file = fopen(bufer, "w");
    file_s = fopen(bufer2, "w");


    for(i = ZERO; i < m; i++)
        fprintf(file, "%lf\n", *(*(matrix + i) + i));

    for(j = ZERO; j < m; j++)
    {
        for(i = ZERO; i < m; i++)
            fprintf(file_s, "%lf, ", *(*(eigenvectores + i) + j));

        fprintf(file_s, "%s", "\n\n");
    }

    printf("Se han creado los archivos en %s\n\n", name_save);
    /*se libera la memoria*/
    free_matrix(matrix, m);
    free_matrix(eigenvectores, m);
    fclose(file);
    fclose(file_s);
}

int main(void)
{
    double eigenvalor, eigenvector1[3];
    double eigenvalor2 = 9;
    double **examen;

    eigenvalor = 10.7;
    eigenvector1[0] = -0.029;
    eigenvector1[1] = -0.098;
    eigenvector1[2] = 1.01;


    examen = matrix_examen();
    print_subes(examen, "Resultados/eigen_vectores_menores.mtx", 10, 1);*/

    /*menores*/
    /*print_test("Materiales/Eigen_3x3.txt", "Resultados/test1.txt", 2, 0);*/

    imprimir_jacobi(examen, "Resultados/eigen_problema4", 2000);


    return ZERO;
}
