#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../print_read/print_read.h"
#define ZERO 0
#define ONE 1

int convergencia(double **matrix, int rows, double *x, double *y, double intervalo)
{
    /*Funcion que resisa la
    convergencia de la solucion, |Ax - b| es muy pequenio*/
    int i, j;
    double sum, number;

    for(i=ZERO; i < rows; i++)
    {
        sum = ZERO;

        /*realiza el producto fila columna*/
        for(j = ZERO; j < rows; j++)
            sum += (*(*(matrix + i) + j)) * (*(x + j));

        /*los elementos de ambos vectores deben ser menores al intervalo*/
        number = fabs(sum - (*(y + i)));

        if(number > intervalo)
            return ONE;

    }

    /*si todos son menores regresa ZERO para detener el ciclo*/
    return ZERO;

}

void jacobi(double **matrix, int rows, double *y, double *x, int *iterations, double error)
{
    /*Solucion a sistema de ecuaciones por el metodo de Jacobi

     Parametros
     ===========
     double matriz: es la matriz con los coeficientes del sistema
     de ecuaciones
     double x: es el vector inicial, es una propuesta de solucion
     double y: es a lo que se igualan el sistema de ecuaciones
     int rows: es el numero de filas, para una matriz cuadrada*/

    int condition = ONE, i, k = ZERO, j;
    double sum;
    double *xk = (double *)calloc(rows, sizeof(double));

    *xk = ONE;

    /*hasta que |Axk - b| ~ 0 se cumpla*/
    while(condition)
    {
        for(i = ZERO; i < rows; i++)
        {
            sum = ZERO;

            for(j = ZERO; j < rows; j++)
            {

                if(j != i)
                    sum += (*(*(matrix + i) + j)) * (*(x + j));

            }

            *(xk + i) = (*(y + i) - sum)/ (*(*(matrix + i) + i));
        }

        condition = convergencia(matrix, rows, xk, y, error);

        for(i = ZERO; i < rows; i++)
            *(x + i) = *(xk + i);

        k++;
        printf("k jacobi %d\n", k);
    }

    *iterations = k;
    free(xk);
}

void solve_jacobi(char *name_mat, char *name_vec, double error)
{
    int m, n, i, k;
    double *y, **matrix, *x;

    /*lectura de datos*/
    y = read_vector(name_vec);
    matrix = leer_matrix_gauss(name_mat, &m);
    x = (double *)calloc(m, sizeof(double));

    /*se propone una solucion*/
    for(i = ZERO; i < m; i++)
        *(x + i) = ONE;

    jacobi(matrix, m, y, x, &k, error);

    printf("El numero de iteraciones es %d, el error absoluto es %.12lf\n", k, error);
    printf("La solucion es:\n");
    imprime_solucion("Resultados/jacobi.vec",x, m);

    free(x);
    free(y);
    free(matrix[0]);
    free(matrix);

}
