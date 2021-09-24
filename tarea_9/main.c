#include <stdio.h>
#include <stdlib.h>
#include "potencia/eigen_potencia.h"
#include "print_read/prdynamic.h"
#define ONE 1
#define ZERO 0

int main()
{
    double **solucion;
    int m;

    solucion = eigen_dominante("test.txt", &m);

    printf("El eigenvalor es: %lf\n", **solucion);

    printf("\nEl eigenvector es:\n");
    print_solucion(*(solucion + ONE), m);

    free_solution_eigen(solucion);
    return ZERO;
}
