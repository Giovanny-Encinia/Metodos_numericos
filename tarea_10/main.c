#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "potencia_inversa/potencia_inversa.h"
#include "eigen_jacobi/eigen_jacobi.h"
#include "print_read/prdynamic.h"
#include <errno.h>
#define ONE 1
#define ZERO 0

void imprimir_resultado_eigen(char *name, char *name_save, int m)
{
    char bufer[100];
    char bufer2[100];
    double *eigen_valores, **eigen_vectores;
    int m_eigen, number_eigen, i, j;
    FILE *f_valor, *f_vector;

    /*Le agrega un sufijo a el archivo, dependiendo si
    son los eigenvalores o eigenvectores*/

    strcat(strcpy(bufer, name_save), "eigen_valores.txt");
    strcat(strcpy(bufer2, name_save), "eigen_vectores.txt");
    f_valor = fopen(bufer, "w");
    f_vector = fopen(bufer2, "w");

    eigen_valores = NULL;
    eigen_vectores = NULL;

    /*restricciones que se piden en la tarea*/
    if(m > 6)
        m_eigen = m - 4;
    else
        m_eigen = 2;

    printf("======================================\n");
    printf("Metodo deflacion potencia inversa\n");
    printf("======================================\n");
    /*crea memoria para almacenar los resultados*/
    eigen_valores = (double *)malloc(m_eigen * sizeof(double));
    eigen_vectores = eigen_menores(name, &number_eigen, eigen_valores, eigen_vectores, m_eigen);

    /*imprime los eigenvectores en el archivo correspondiente*/
    for(i = ONE; i < m_eigen + ONE; i++)
    {
        for(j = ZERO; j < m; j++)
            fprintf(f_vector, "%lf, ", *(*(eigen_vectores + i) + j));

        /*cada eigenvector tendra la separacionn \n\n*/
        fprintf(f_vector, "\n\n");

    }

    /*imprime los eigenvalores en el archivo correspondiente*/
    for(i = ZERO; i < m_eigen; i++)
    {
        fprintf(f_valor, "%lf, ", *(eigen_valores + i));
        fprintf(f_valor, "\n");
    }

    printf("archivos generados en %s\n", name_save);

    /*libera toda la memoria dinamica*/
    free(eigen_valores);

    for(i = ONE; i < m_eigen - ONE; i++)
        free(*(eigen_vectores + i));

    free(eigen_vectores);
    /*cierra archivos*/
    fclose(f_valor);
    fclose(f_vector);


}

void imprimir_jacobi(char *name, char *name_save, int tamanio)
{
    /*Lee una matriz en txt y retorna una matriz creada dinamicamente*/

    int m, n, i, j;
    char bufer[100];
    char bufer2[100];
    double **matrix, **eigenvectores;
    FILE *file, *file_s;

    strcat(strcpy(bufer, name_save), "eigen_valores.txt");
    strcat(strcpy(bufer2, name_save), "eigen_vectores.txt");
    /*la matriz se guarda como un vector, pero se
    puede acceder de manera estandar a cada uno de sus elementos*/
    matrix = read_matrix_file(name, &m, &n, ZERO);
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
    /*Archivo de prueba*/
    imprimir_resultado_eigen("Materiales/Eigen_3x3.txt", "Resultados/deflacion_inversa/_3x3_", 3);
    /*Archivos para la tarea*/
    /*
    imprimir_resultado_eigen("Materiales/Eigen_3x3.txt", "Resultados/deflacion_inversa/_3x3_", 3);
    imprimir_resultado_eigen("Materiales/Eigen_50x50.txt", "Resultados/deflacion_inversa/_50x50_", 50);
    imprimir_resultado_eigen("Materiales/Eigen_500x500.txt", "Resultados/deflacion_inversa/_500x500_", 500);
    imprimir_resultado_eigen("Materiales/Eigen_1000x1000.txt", "Resultados/deflacion_inversa/_1000x1000_", 1000);*/

    imprimir_jacobi("Materiales/Eigen_3x3.txt", "Resultados/jacobi/_3x3_", 3);
    /*imprimir_jacobi("Materiales/Eigen_50x50.txt", "Resultados/jacobi/_50x50_", 50);*/
    /*imprimir_jacobi("Materiales/Eigen_125x125.txt", "Resultados/jacobi/_125x125_", 125);*/


    return ZERO;
}
