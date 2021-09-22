#include <stdio.h>
#include <stdlib.h>
#include "difrerencias_finitas_calor/calor.h"
#include "jacobi/jacobi.h"
#include "gauss_seidel/gauss_seidel.h"
#define ZERO 0
#define ONE 1
#define ELEMENTOS 10

void print_distancia_temp(char *name, int elementos, double Q)
{
    /*Esto no lo pide la tarea pero si variamos la Q, la grafica
    cambia*/
    int i;
    double *x, x_delta = ZERO;

    /*imprime la distancia vs la temperatura*/
    FILE *f = fopen(name, "w");

    x = solve_calor_diferencias_finitas(Q, 5, 10, 20, elementos, ONE);
    printf("--------------------------------------------------------\n");

    for(i = ZERO; i < elementos - ONE; i++)
    {
        x_delta += 1.0/elementos;
        fprintf(f, "%lf %lf\n", x_delta, *(x + i));
    }

    fclose(f);
    free(x);

}

void print_calor(int *ar)
{
    int i, index;
    double *x = ZERO;
    FILE *f = fopen("datos_calor/nodo_mitad_temperatura.txt", "w");
    /*imprime la distancia vs la temperatura*/

    print_distancia_temp("datos_calor/distancia_temperatura_10.txt", 10, 3);
    print_distancia_temp("datos_calor/distancia_temperatura_100.txt", 10, 3);
    printf("Solucion Con Q=300");
    print_distancia_temp("datos_calor/distancia_temperatura_100_Qmayor.txt", 100, 300);

    for(i = ZERO; i < 5; i++)
    {
        printf("--------------------------------------------------------\n");
        x = solve_calor_diferencias_finitas(3, 5, 10, 20, *(ar + i), ONE);
        index = (*(ar + i) - ONE) / 2;
        fprintf(f, "%d %lf\n", *(ar + i), *(x + index));
    }

    free(x);
    fclose(f);
}

int main(void)
{
    char opcion;
    double error = 1E-12, *x;
    int ar[] = {10, 30, 50, 70, 100};

    printf("\t1- Resultados Diferencias finitas\n");
    printf("\t2- Resultado Jacobi vs. Resultado Gauss-Seidel\n");
    printf("\n\tElige una opcion\t");

    scanf(" %c", &opcion);

    printf("========================================================\n");
    switch(opcion)
    {
    case '1':
        printf("\t\tDiferencias finitas calor\n");
        printf("--------------------------------------------------------\n");
        x = solve_calor_diferencias_finitas(3, 5, 10, 20, 4, 1);
        free(x);
        print_calor(ar);
        break;
    case '2':
        printf("\t\tSolucion Jacobi 3x3\n");
        printf("--------------------------------------------------------\n");
        solve_jacobi("Materiales/M_sys_3x3.txt", "Materiales/V_sys_3x1.txt", error);
        printf("\n========================================================\n");
        printf("\t\tSolucion Gauss-Seidel 3x3\n");
        printf("--------------------------------------------------------\n");
        solve_gauss_seidel("Materiales/M_sys_3x3.txt", "Materiales/V_sys_3x1.txt", error);
        printf("\n========================================================\n");
        printf("\t\tSolucion Jacobi 125x125\n");
        printf("--------------------------------------------------------\n");
        solve_jacobi("Materiales/M_sys_125x125.txt", "Materiales/V_sys_125x1.txt", error);
        printf("\n========================================================\n");
        printf("\t\tSolucion Gauss-Seidel 125x125\n");
        printf("--------------------------------------------------------\n");
        solve_gauss_seidel("Materiales/M_sys_125x125.txt", "Materiales/V_sys_125x1.txt", error);
        break;
    }

    printf("========================================================\n");

    return ZERO;
}
