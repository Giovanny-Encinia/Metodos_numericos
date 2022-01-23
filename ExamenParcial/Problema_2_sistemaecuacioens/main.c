#include <stdio.h>
#include <stdlib.h>
#include "print_read/prdynamic.h"
#include "gauss_pivoteo_total/solve_gauss_pt.h"
#include "LU/factorization_lu.h"
#define ZERO 0
#define NORMAL ZERO

void gauss_pivote_show(char *namem, char * namev)
{
    int rows = ZERO, cols = ZERO, r_a = ZERO, su;

/*================Inicializa datos para GAUSS PIVOTE=================*/
    double *y = read_array_file(namev, &r_a);/* es la variable dependiente f(x)*/
    double **matrix = read_matrix_file_2(namem, &rows, &cols);
    double *x = (double *)malloc(r_a*sizeof(double)); /* se guarda la solucion*/
    int signo, i; /*para saber sobre el determinante*/
    FILE *file;
/*===================================================================*/

	if(matrix==NULL)
    {
		printf("\nEs nula\n");
	}

    /*Gauss por pivoteo necesita un almacenamiento distinto*/

    printf("================================================================\n\n");
    printf("            GAUSS PIVOTE\n\n");
    printf("================================================================\n\n");
    /*printf("La matriz es:\n");
    print_matrix(matrix, rows, rows);*/

    /*printf("\nEl array es:\n");
    print_array(y, r_a);*/
    su = gauss(matrix, rows, x, y, &signo);
    file = fopen("Resultados/solucion_problema2.vec", "w");

    fprintf(file, "%d %d\n", r_a, 1);

    if(su)
    {

        for(i = 0; i < r_a; i++)
            fprintf(file, "%9lf\n" , x[i]);

    }

    printf("La solucion esta en: Resultados/solucion_problema2.vec\n");

    free(y);
    free_expanded_matrix(matrix, rows);
	free(x);

}

void lu_show(char *namem, char * namev)
{
    int rows = ZERO, cols = ZERO, r_a = ZERO, su, i;
    /*double *y = read_array_file(namev, &r_a);*/
    double **matrix = read_matrix_file(namem, &rows, &cols, NORMAL);
    double *x = (double *)malloc(r_a*sizeof(double));
    double *z;

    su = solve_lu(matrix, rows, x, z);

    free(x);
    free_matrix(matrix, rows);

}

int main(void)
{
    printf("RESULTADOS Examen\n");
    /*gauss_pivote_show("Materiales/A_1000.mtx", "Materiales/b_1000.vec");*/
    lu_show("Materiales/A_1000.mtx", "jia");

	return ZERO;
}
