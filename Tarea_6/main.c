#include <stdio.h>
#include <stdlib.h>

#include "print_read/prdynamic.h"
#include "diagonal/solve_diagonal.h"
#include "gauss_pivoteo_total/solve_gauss_pt.h"
#include "inferior/solve_inferior.h"
#include "superior/solve_superior.h"

#define ZERO 0
#define ONE 1
#define NORMAL ZERO
#define SUPERIOR 1
#define DIAGONAL 2
#define INFERIOR 3

void solve_method(int type_solve, char *name_file, char *name_f_sol)
{
    int rows = ZERO, cols = ZERO, r_a = ZERO;

	double** matrix = read_matrix_file(name_file, &rows, &cols, type_solve);
    double* y = read_array_file(name_f_sol, &r_a);/* es la variable dependiente f(x)*/
    double * x = (double *)malloc(r_a*sizeof(double)); /* se guarda la solucion*/


	if(matrix==NULL)
    {
		printf("\nEs nula\n");
	}



	switch(type_solve)
	{
    case DIAGONAL:
        printf("================================================================\n\n");
        printf("            DIAGONAL\n\n");
        printf("================================================================\n\n");
        solve_diagonal(matrix, r_a, x, y);
        printf("La matriz es:\n");
        print_diagonal(matrix, rows, cols);
        break;
    case SUPERIOR:
        printf("================================================================\n\n");
        printf("            SUPERIOR\n\n");
        printf("================================================================\n\n");
        printf("La matriz es:\n");
        solve_triangular_super(matrix, rows, cols, x, y, ONE);
        print_triangular_matrix(matrix, rows, cols, SUPERIOR);
        break;
    case INFERIOR:
        printf("================================================================\n\n");
        printf("            INFERIOR\n\n");
        printf("================================================================\n\n");
        printf("La matriz es:\n");
        solve_triangular_infer(matrix, rows, cols, x, y);
        print_triangular_matrix(matrix, rows, cols, INFERIOR);
        break;

	}

	printf("\nEl array es:\n");
    print_array(y, r_a);
    printf("\nLa solucion es\n");
    print_solucion(x, r_a);
    printf("\n");

	free_array(y);
	free_matrix(matrix, rows);
	free(x);
}

int main()
{
    int rows = ZERO, cols = ZERO, r_a = ZERO;

/*================Inicializa datos para GAUSS PIVOTE=================*/
    double* y = read_array_file("Materiales/V_LARGE.txt", &r_a);/* es la variable dependiente f(x)*/
    double** matrix = read_matrix_file_2("Materiales/M_LARGE.txt", &rows, &cols);
    double * x = (double *)malloc(r_a*sizeof(double)); /* se guarda la solucion*/
    int signo; /*para saber sobre el determinante*/
/*===================================================================*/

	if(matrix==NULL)
    {
		printf("\nEs nula\n");
	}

	/*Llama a los otros metodos*/
    solve_method(DIAGONAL, "Materiales/M_DIAG.txt", "Materiales/V_DIAG.txt");
    solve_method(SUPERIOR, "Materiales/M_TSUP.txt", "Materiales/V_TSUP.txt");
    solve_method(INFERIOR, "Materiales/M_TINF.txt", "Materiales/V_TINF.txt");

    /*Gauss por pivoteo necesita un almacenamiento distinto*/

    printf("================================================================\n\n");
    printf("            GAUSS PIVOTE\n\n");
    printf("================================================================\n\n");
    printf("La matriz es:\n");

    printf("Por motivos de estetica no se imprime la matriz\n");
    gauss(matrix, rows, x, y, &signo);
    printf("\nEl array es:\n");
    print_array(y, r_a);
    printf("\nLa solucion es\n");
    print_solucion(x, r_a);
    printf("\n");


	free_array(y);
	free_expanded_matrix(matrix, rows);
	free(x);

	return ZERO;
}
