#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayleigh/rayleigh.h"
#include "print_read/prdynamic.h"
#ifndef ZERO
#define ZERO 0
#endif/*ZERO*/

int main(void)
{
    double *eigenvector, eigenvalor, **matrix;
    int i, m, n;


    matrix = read_matrix_file("Materiales/test.txt", &m, &n, ZERO);
    eigenvector = (double *)calloc(m, sizeof(double));
    eigenvalor = 10.7;
    
    for(i = ZERO; i < m; i++)
        *(eigenvector + i) = 1/sqrt(m);

    eigenvector[0] = -0.029;
    eigenvector[1] = -0.098;
    eigenvector[2] = 1.01;
    
    rayleigh_eigen(matrix, m, &eigenvalor, eigenvector);

    printf("El eigenvalor es: %lf\n", eigenvalor);

    free(eigenvector);
    free_matrix(matrix, m);
}