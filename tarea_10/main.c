#include <stdio.h>
#include <stdlib.h>
#include "potencia_inversa/potencia_inversa.h"
#include "print_read/prdynamic.h"
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

    eigen_valores = (double *)malloc(m_eigen * sizeof(double));
    eigen_vectores = eigen_menores(name, &number_eigen, eigen_valores, eigen_vectores, m_eigen);

    for(i = ONE; i < m_eigen + ONE; i++)
    {
        for(j = ZERO; j < m; j++)
            fprintf(f_vector, "%lf, ", *(*(eigen_vectores + i) + j));


        fprintf(f_vector, "\n\n");

    }

    for(i = ZERO; i < m_eigen; i++)
    {
        fprintf(f_valor, "%lf, ", *(eigen_valores + i));
        fprintf(f_valor, "\n");
    }

    free_expanded_matrix(eigen_vectores, m_eigen + ONE);
    free(eigen_valores);
    fclose(f_vector);
    fclose(f_valor);



}

int main()
{
    imprimir_resultado_eigen("Materiales/Eigen_7x7.txt", "Resultados/_7x7_", 13);
    return ZERO;
}
