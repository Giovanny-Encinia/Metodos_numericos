#include <stdio.h>
#include "QR/QR.h"
#include "print_read/print_read.h"
#include "matrix_math/matrix_math.h"

void imprime_eigen(char *name, char *name_save, char *name_save2)
{
    double **matrix, *eigenvalores, **resultado, **matrix_t;
    double *av, *valv, **matrix2;
    int m, n, i, j;
    FILE *f_valores, *f_vectores;

    f_vectores = fopen(name_save, "w");
    f_valores = fopen(name_save2, "w");

    matrix = read_matrix_file_2(name, &m, &n);
    /*En matrix se encuentran los eigenvectores*/
    eigenvalores = qr_eigen(matrix, m);

    fprintf(f_vectores, "%d %d\n", m, n);

    for (i = 0; i < m; i++)
    {

        for(j = 0; j < m; j++)
            fprintf(f_vectores, "%.9lf ", *(*(matrix + i) + j));
        
        fprintf(f_vectores, "\n");
    }

    fprintf(f_valores, "%d\n", m);

    for (i = 0; i < m; i++)
        fprintf(f_valores, "%.9lf\n", *(eigenvalores + i));

    printf("Los resultados estan en:\n%s\n%s\n", \
    name_save, name_save2);

    free_expanded_matrix(matrix, m);
    free_array(eigenvalores);

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