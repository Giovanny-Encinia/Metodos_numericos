#include <stdio.h>
#include <stdlib.h>
#include "potencia/eigen_potencia.h"
#include "potencia_inversa/potencia_inversa.h"
#include "m_eigenvalores_mayores/m_eigenvalores_mayores.h"
#include "print_read/prdynamic.h"
#define ONE 1
#define ZERO 0

int main()
{
    double **solucion, **sol_m, *em;
    int m;

    solucion = eigen_dominante("test.txt", &m);

    printf("El eigenvalor dominante es: %lf\n", **solucion);

    printf("El eigenvector es:\n");
    print_solucion(*(solucion + ONE), m);

    sol_m = eigen_menor("test.txt", &m);

    printf("El eigenvalor minimo es: %lf\n", **sol_m);

    printf("El eigenvector es:\n");
    print_solucion(*(sol_m + ONE), m);


    printf("Eigen mayores:\n");
    eigen_mayores("test.txt", &m, 2);


    free_solution_eigen(sol_m);
    free_solution_eigen(solucion);

    return ZERO;
}
