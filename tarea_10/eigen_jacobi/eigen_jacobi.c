#include <stdio.h>
#include <stdlib.h>
#define ZERO 0
#define ONE 1

void mayor_absoluto(double **matrix, int m, int *i, int *j)
{
    /*Funcion que encuentra el mayor valor absoluto
    fuera de la diagonal, una vez encontrado retorna los
    indices de dicho elemento

    Parametros
    ==========
    double **matrix: es la matriz en donde se efectuara la busqueda
    int m: es la dimension de la matriz
    int *i: es la variable en donde se almacenara el indice
    asociado a la fila
    int *j: aqui se guardara el indice asociado a la columna*/

    int k, l;
    double mayor;

    mayor = *(*(matrix) + ONE);

    for(k = ZERO; k < m; k++)
    {
        for(l = ZERO; l < m ; l++)
        {
            /*ignoramos los elementos de la diagonal*/
            if(k != l)
            {
                if(*(*(matrix + k) + l) >= mayor)
                {
                    *i = k;
                    *j = l;
                    mayor = *(*(matrix + k) + l);
                }
            }

        }
    }
}

double **eigen_jacobi(double **matrix, int m)
{
    /*Funcion que usa el metodo de Jacobi para
    calcular eigenpares

    Paramtro
    ========
    double **matrix: es donde se guardan los coeficientes de l amatriz
    int m: es la dimension de la matriz

    Return
    ======
    double **eigenvectores: retorna una matriz con los eigenvectores como columnas
    de la matriz*/

    int i, j;

    mayor_absoluto(matrix, m, &i, &j);

    printf("El mayor elemento es %lf\n", *(*(matrix + i) + j));
}

void leer(char *name)
{
    /*Lee una matriz en txt y retorna una matriz creada dinamicamente*/

    int m, n;
    double **matrix, **eigenvectores;

    /*la matriz se guarda como un vector, pero se
    puede acceder de manera estandar a cada uno de sus elementos*/
    matrix = read_matrix_file(name, &m, &n, ZERO);
    eigenvectores = eigen_jacobi(matrix, m);
    free_matrix(matrix, m);
}
