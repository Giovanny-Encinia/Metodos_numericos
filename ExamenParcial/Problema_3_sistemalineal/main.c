#include <stdio.h>
#include <stdlib.h>
#include "gauss_seidel/gauss_seidel.h"
#include "print_read/print_read.h"
#include "diagonal/solve_diagonal.h"
#include "gauss_pivoteo_total/solve_gauss_pt.h"
#include "jacobi/jacobi.h"
#define ZERO 0
#define ONE 1
#define ELEMENTOS 10

void gauss_pivote_show(char *namem, char *namev)
{
    int rows = ZERO, cols = ZERO, r_a = ZERO, su;

    /*================Inicializa datos para GAUSS PIVOTE=================*/
    double *y = read_vector(namev); /* es la variable dependiente f(x)*/
    double **matrix = leer_matrix_gauss(namem, &rows);
    double *x = (double *)malloc(rows * sizeof(double)); /* se guarda la solucion*/
    int signo, i;                                       /*para saber sobre el determinante*/
    FILE *file;
    /*===================================================================*/

    if (matrix == NULL)
    {
        printf("\nEs nula\n");
    }

    /*Gauss por pivoteo necesita un almacenamiento distinto*/

    printf("================================================================\n\n");
    printf("            Gauss Pivote\n\n");
    printf("================================================================\n\n");
    /*printf("La matriz es:\n");
    print_matrix(matrix, rows, rows);*/

    /*printf("\nEl array es:\n");
    print_array(y, r_a);*/
    gauss(matrix, rows, x, y, &signo);
    file = fopen("Resultados/gauss_pivote.vec", "w");

    
    fprintf(file, "%d %d\n", rows, 1);

    for (i = 0; i < rows; i++)
        fprintf(file, "%.9lf\n", x[i]);


    printf("La solucion esta en: Resultados/gauss_pivote.vec\n");

    free(y);
    
    for(i = 0; i < rows; i++)
        free(matrix[i]);
    
    free(matrix);

    free(x);
}

int main(void)
{
    char opcion;
    double error = 1E-12, **matrix, *x, *y;
    int i, m;

    i = es_diagonal("Materiales/A_3134.mtx");

    if(i)
    {
        printf("Se puede usar metodo de matriz diagonal\n");
    }

    matrix = leer_examen_diagonal("Materiales/A_3134.mtx", &m);
    /*aqui se almacenan las soluciones*/
    x = (double *)calloc(m, sizeof(double));
    y = read_vector("Materiales/b_3134.vec");
    printf("================================================================\n\n");
    printf("            Metodo Diagonal\n\n");
    printf("================================================================\n\n");
    solve_diagonal(matrix, m, x, y);
    imprime_solucion("Resultados/diagonal.vec", x, m);
    printf("================================================================\n\n");
    printf("            Gauss Seidel\n\n");
    printf("================================================================\n\n");
    solve_gauss_seidel("Materiales/A_3134.mtx", "Resultados/diagonal.vec", 1E-12);
    gauss_pivote_show("Materiales/A_3134.mtx", "Materiales/b_3134.vec");
    printf("================================================================\n\n");
    printf("            Jacobi\n\n");
    printf("================================================================\n\n");
    solve_jacobi("Materiales/A_3134.mtx", "Materiales/b_3134.vec", 1E-12);

    free(matrix[0]);
    free(matrix);

    free(x);
    free(y);
    /*
    printf("\n========================================================\n");
    printf("\t\tSolucion Gauss-Seidel 3x3\n");
    printf("--------------------------------------------------------\n");
    solve_gauss_seidel("Materiales/M_sys_3x3.txt", "Materiales/V_sys_3x1.txt", error);
    printf("\n========================================================\n");
   
      
 

    printf("========================================================\n");*/

    return ZERO;
}
