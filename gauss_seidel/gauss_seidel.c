#include <stdlib.h>
#include <math.h>
#include "../print_read/prdynamic.h"
#define ZERO 0
#define ONE 1

int convergencia_gs(double **matrix, int rows, double *x, double *y)
{
    /*Funcion que resisa la
    convergencia de la solucion, |Ax - b| es muy pequenio*/
    int i, j;
    double intervalo = 0.0000001, sum, number;

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

void gauss_seidel(double **matrix, int rows, double *y, double *x, int *iterations)
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

    /*hasta que |Axk - b| ~ 0 se cumpla*/
    while(condition)
    {
        for(i = ZERO; i < rows; i++)
        {
            sum = ZERO;

            /*sum_{0}^{i-1}a_{i,j}x_{j}^{n+1}*/
            /*sum_{i+1}^{n}a_{i,j}x_{j}^{n}*/
            for(j = ZERO; j < rows; j++)
            {

                if(j != i)
                    sum += (*(*(matrix + i) + j)) * (*(x + j));

            }


            *(x + i) = (*(y + i) - sum)/ (*(*(matrix + i) + i));
        }

        condition = convergencia_gs(matrix, rows, x, y);

        k++;
    }

    *iterations = k;
}

void *solve_gauss_seidel(char *name_mat, char *name_vec)
{
    int m, n, i, k;
    double *y, **matrix, *x;

    /*lectura de datos*/
    y = read_array_file(name_vec, &m);
    matrix = read_matrix_file(name_mat, &m, &n, ZERO);
    x = (double *)calloc(m, sizeof(double));

    /*se propone una solucion*/
    for(i = ZERO; i < m; i++)
        *(x + i) = ONE;

    gauss_seidel(matrix, m, y, x, &k);

    printf("El numero de iteraciones es: %d\n", k);
    printf("La solucion es:\n");
    print_solucion(x, m);

    free(x);
    free(y);
    free_matrix(matrix, m);

}
