#include <stdio.h>
#include <stdlib.h>
#include "print_read/prdynamic.h"
#include "gauss_pivoteo_total/solve_gauss_pt.h"
#include "LU/factorization_lu.h"
#include "cholesky/cholesky.h"
#include "funciones_generadoras_matrices/funcion_generadora_mat.h"
#define ZERO 0
#define NORMAL ZERO

void gauss_pivote_show(char *namem, char * namev)
{
    int rows = ZERO, cols = ZERO, r_a = ZERO, su;

/*================Inicializa datos para GAUSS PIVOTE=================*/
    double *y = read_array_file(namev, &r_a);/* es la variable dependiente f(x)*/
    double **matrix = read_matrix_file_2(namem, &rows, &cols);
    double *x = (double *)malloc(r_a*sizeof(double)); /* se guarda la solucion*/
    int signo; /*para saber sobre el determinante*/
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

    if(su)
    {
        printf("\nLa solucion es\n");
        print_solucion(x, r_a);
        printf("\n");
    }

    free(y);
	free_expanded_matrix(matrix, rows);
	free(x);

}

void lu_show(char *namem, char * namev)
{
       int rows = ZERO, cols = ZERO, r_a = ZERO, su;

/*================Inicializa datos para GAUSS PIVOTE=================*/
    double *y = read_array_file(namev, &r_a);/* es la variable dependiente f(x)*/
    double **matrix = read_matrix_file(namem, &rows, &cols, NORMAL);
    double *x = (double *)malloc(r_a*sizeof(double)); /* se guarda la solucion*/
/*===================================================================*/

    if(matrix==NULL)
    {
		printf("\nEs nula\n");
	}

    /*Gauss por pivoteo necesita un almacenamiento distinto*/

    printf("================================================================\n\n");
    printf("            LU\n\n");
    printf("================================================================\n\n");
    /*printf("La matriz es:\n");
    print_matrix(matrix, rows, rows);*/
    /*printf("\nEl array es:\n");
    print_array(y, r_a);*/
    su = solve_lu(matrix, rows, x, y);
    /*print_matrix(matrix, rows, rows);*/

    if(su)
    {
        printf("\nLa solucion es\n");
        print_solucion(x, r_a);
        printf("\n");
    }

    free(y);
    free(x);
    free_matrix(matrix, rows);

}

void cholesky_show(int rows, char *namel, char * named, char *namelt)
{
    double **matrix;
    double (*f)(int, int);
    f = &funcion_generadora_1;

    printf("================================================================\n\n");
    printf("            CHOLESKY\n\n");
    printf("================================================================\n\n");
    /*la matriz que se genera es una matriz triagular inferior
    colapsada, create_space_cholesky se usa cuando son matrices generadas
    con alguna funcion*/
    matrix = create_space_cholesky(rows);
    /*crea una matriz con la info de los tres factores*/
    cholesky(matrix, rows, f);
    /*imprime los factores en pantalla*/
    /*print_cholesky(matrix, rows);*/

    /*los fatores son guardados en un txt*/
    cholesky_to_txt(matrix, rows, namel, named, namelt);
    free_matrix(matrix, rows);
}

int main(void)
{
    printf("RESULTADOS PARA SMALL\n");
    gauss_pivote_show("Materiales/M_SMALL.txt", "Materiales/V_SMALL.txt");
    lu_show("Materiales/M_SMALL.txt", "Materiales/V_SMALL.txt");
    printf("\n\n\n");
    printf("RESULTADOS PARA LARGE\n");
    gauss_pivote_show("Materiales/M_LARGE.txt", "Materiales/V_LARGE.txt");
    lu_show("Materiales/M_LARGE.txt", "Materiales/V_LARGE.txt");
    printf("\n\n\n");
    printf("CHOLESKY 4, 50, 100\n");
    cholesky_show(4,"resultados_cholesky/LN.txt", "resultados_cholesky/DN.txt", "resultados_cholesky/LTN.txt");
    cholesky_show(50,"resultados_cholesky/LN_50.txt", "resultados_cholesky/DN_50.txt", "resultados_cholesky/LTN_50.txt");
    cholesky_show(100,"resultados_cholesky/LN_100.txt", "resultados_cholesky/DN_100.txt", "resultados_cholesky/LTN_100.txt");

	return ZERO;
}
