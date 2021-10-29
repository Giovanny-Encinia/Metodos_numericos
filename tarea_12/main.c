#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "QR/QR.h"
#include "print_read/print_read.h"
#include "matrix_math/matrix_math.h"

void imprime_eigen(char *name, char *name_save, char *name_save2)
{
    double **matrix, *eigenvalores, **resultado, **matrix_t;
    double **av, **valv, **matrix2, denominador = ZERO;
    double numerador = ZERO;
    int m, n, i, j;
    FILE *f_valores, *f_vectores;

    f_vectores = fopen(name_save, "w");
    f_valores = fopen(name_save2, "w");

    matrix = read_matrix_file_2(name, &m, &n);
    /*En matrix se encuentran los eigenvectores*/
    eigenvalores = qr_eigen(matrix, m);
    /*aniade las dimensiones de la matriz*/
    fprintf(f_vectores, "%d %d\n", m, n);

    /*imprime los resultados de la matriz*/
    for (i = 0; i < m; i++)
    {

        for(j = 0; j < m; j++)
            fprintf(f_vectores, "%.13lf ", *(*(matrix + i) + j));
        
        fprintf(f_vectores, "\n");
    }

    /*aniade la dimension del vector*/
    fprintf(f_valores, "%d\n", m);

    /*imprime los eigenvalores*/
    for (i = 0; i < m; i++)
        fprintf(f_valores, "%.13lf\n", *(eigenvalores + i));

    printf("Los resultados estan en:\n%s\n%s\n", \
    name_save, name_save2);

    /*se lee de nuevo la matriz original*/
    matrix2 = read_matrix_file_2(name, &m, &n);
    /*producto punto de matriz original y eigenvectores*/
    av = dot_matrix(matrix2, matrix, m, m, m, m);
    valv = (double **)calloc(m, sizeof(double **));
    *valv = (double *)calloc(m * m, sizeof(double));

    for(i = ONE; i < m; i++)
        *(valv + i) = *(valv + i - ONE) + m;

    /*producto punto de eigenvalores en matriz y eigenvectores*/
    for(i = ZERO; i < m; i++)
    {
        for(j = ZERO; j < m; j++)
            *(*(valv + i) + j) = *(*(matrix+ i) + j) * (*(eigenvalores + i));
    }

    for(i = ZERO; i < m; i++)
    {

        for(j = ZERO; j < m; j++)
            denominador += (*(*(av + i) + j)) * (*(*(av + i) + j));

    }

    denominador = sqrt(denominador);

    for (i = ZERO; i < m; i++)
    {

        for (j = ZERO; j < m; j++)
            numerador +=\
            (av[i][j] - valv[i][j]) * (av[i][j] - valv[i][j]);

    }

    numerador = sqrt(numerador);

    printf("La comprobacion nos da: %lf\n", numerador / denominador);

    free_expanded_matrix(matrix, m);
    free_expanded_matrix(matrix2, m);
    free_array(eigenvalores);
    free_matrix(av, m);
    free_matrix(valv, m);

    fclose(f_valores);
    fclose(f_vectores);
}

int main(void)
{
    imprime_eigen("Materiales/Eigen_3.txt", "Resultados/3_evectors.txt",
                  "Resultados/3_evalues.txt");
    imprime_eigen("Materiales/Eigen_25.txt", "Resultados/25_evectors.txt",
                  "Resultados/25_evalues.txt");

    return 0;
}