#include <stdio.h>
#include "QR/QR.h"
#include "print_read/print_read.h"
#include "matrix_math/matrix_math.h"

int main(void)
{
    double **matrix, **r, **resultado, **matrix_t;
    int m, n;

    matrix = read_matrix_file_2("test.txt", &m, &n);
    matrix_t = traspuesta(matrix, m, m);
    r = qr_factor(matrix_t, m);

    print_matrix(matrix_t, m, m);
    printf("R\n");
    print_matrix(r, m, m);
    resultado = dot_matrix(matrix_t, r, m, m, m, m);
    printf("Original con QR\n");
    print_matrix(resultado, m, m);
    free_expanded_matrix(matrix, m);
    free_matrix(r, m);
    free_matrix(resultado, m);
    free_matrix(matrix_t, m);

    return 0;
}