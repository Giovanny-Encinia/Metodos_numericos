#include <stdio.h>
#include <stdlib.h>
#include "potencia_inversa/potencia_inversa.h"
#include "print_read/prdynamic.h"
#define ONE 1
#define ZERO 0

void imprimir_resultado_eigen(char *name, int t, char *name_save, int normalizar_)
{
    double **solucion, **sol_m;
    int m;

    eigen_menores(name, &m);


}

int main()
{
    imprimir_resultado_eigen("test.txt", 3, "Resultados/Eigen_3.txt", 2);
    return ZERO;
}
