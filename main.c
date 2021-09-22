#include <stdio.h>
#include <stdlib.h>
#include "difrerencias_finitas_calor/calor.h"
#include "jacobi/jacobi.h"
#define ZERO 0
#define ONE 1
#define ELEMENTOS 10

int main(void)
{
    char opcion;

    printf("\t1- Resultados Diferencias finitas\n");
    printf("\t2- Resultado metodo de Jacobi\n");
    printf("\t3- Resultado Gauss Seidel\n");
    printf("\n\tElige una opcion");

    scanf(" %c", &opcion);

    printf("========================================================\n");
    switch(opcion)
    {
    case '1':
        printf("\t\tDiferencias finitas calor\n");
        printf("--------------------------------------------------------\n");
        solve_calor_diferencias_finitas(3, 5, 10, 20, 4, ONE);
        printf("--------------------------------------------------------\n");
        solve_calor_diferencias_finitas(3, 5, 10, 20, 100, ONE);
        break;
    case '2':
        printf("\t\tSolucion Jacobi\n");
        printf("--------------------------------------------------------\n");
        solve_jacobi("test_mat.txt", "test_vec.txt");
        break;
    case '3':
        printf("\t\tSolucion Gauss-Seidel\n");
        printf("--------------------------------------------------------\n");
        solve_gauss_seidel("test_mat.txt", "test_vec.txt");
        break;
    }

    printf("========================================================\n");

    return ZERO;
}
