#include <stdio.h>
#include <stdlib.h>
#include "potencia/eigen_potencia.h"
#include "potencia_inversa/potencia_inversa.h"
#include "m_eigenvalores_mayores/m_eigenvalores_mayores.h"
#include "print_read/prdynamic.h"
#include "m_eigenvalores_mayores/m_eigenvalores_mayores.h"
#define ONE 1
#define ZERO 0

void imprimir_resultado_eigen(char *name, int t, char *name_save, int normalizar_)
{
    double **solucion, **sol_m;
    int m;
    FILE *file;

    printf("\t========================");
    printf("===========================================================\n");
    printf("\t|%40s%3dx%3d%35s\n", "Matriz",t, t, "|");
    printf("\t========================");
    printf("===========================================================\n");
    printf("\t|Eigen Dominante%67s\n", "|");
    printf("\t------------------------");
    printf("-----------------------------------------------------------\n");
    solucion = eigen_dominante(name, &m);
    printf("\tEigenvalor: %lf\n", **solucion);
    printf("\tEigenvector:\n");
    print_solucion(*(solucion + ONE), m);

    printf("\t------------------------");
    printf("-----------------------------------------------------------\n");


    printf("\t|Eigen Menor%71s\n", "|");
    printf("\t------------------------");
    printf("-----------------------------------------------------------\n");
    sol_m = eigen_menor(name, &m);
    printf("\tEigenvalor: %lf\n", **sol_m);
    printf("\tEigenvalor\n");
    print_solucion(*(sol_m + ONE), m);
    printf("\t========================");
    printf("===========================================================\n");
    printf("\n");

    printf("\tEigen mayores:\n");
    eigen_m(name, &m, normalizar_);
    free_solution_eigen(sol_m);
    free_solution_eigen(solucion);
}

int main()
{
    imprimir_resultado_eigen("Materiales/Eigen_3x3.txt", 3, "Resultados/Eigen_3.txt", 2);
    imprimir_resultado_eigen("Materiales/Eigen_50x50.txt", 50, "Resultados/Eigen_50.txt", 2);
    imprimir_resultado_eigen("Materiales/Eigen_125x125.txt", 125, "Resultados/Eigen_125.txt", 0);

    return ZERO;
}
