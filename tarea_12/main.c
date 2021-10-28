#include <stdio.h>
#include "QR/QR.h"
#include "print_read/print_read.h"
#include "matrix_math/matrix_math.h"

int main(void)
{
    double **matrix, *eigenvalores, **resultado, **matrix_t;
    int m, n;

    matrix = read_matrix_file_2("test.txt", &m, &n);
    eigenvalores = qr_eigen(matrix, m);

    printf("eigenvectores:\n");
    print_matrix(matrix, m, m);
    printf("Eigenvalores\n");
    print_solucion(eigenvalores, m);
    free_expanded_matrix(matrix, m);
    free_array(eigenvalores);

    return 0;
}