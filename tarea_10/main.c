#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "potencia_inversa/potencia_inversa.h"
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
    free_expanded_matrix(eigen_vectores, m_eigen + ONE);
    /*cierra archivos*/
    fclose(f_valor);
    fclose(f_vector);


}

int main(void)
{
    /*Archivo de prueba*/
    /*imprimir_resultado_eigen("Materiales/Eigen_3x3.txt", "Resultados/_3x3_", 3);*/
    /*Archivos para la tarea*/
    /*
    imprimir_resultado_eigen("Materiales/Eigen_3x3.txt", "Resultados/_3x3_", 3);
    imprimir_resultado_eigen("Materiales/Eigen_50x50.txt", "Resultados/_50x50_", 50);
    imprimir_resultado_eigen("Materiales/Eigen_500x500.txt", "Resultados/_500x500_", 500);
    imprimir_resultado_eigen("Materiales/Eigen_1000x1000.txt", "Resultados/_1000x1000_", 1000);*/

    leer("test.txt");

    return ZERO;
}
