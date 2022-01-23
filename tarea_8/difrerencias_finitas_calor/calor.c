#include <stdlib.h>
#include <stdio.h>
#define ZERO 0
#define ONE 1
#define TWO 2

void solve_calor_inferior(double **matrix, double *y, int rows, double *w)
{
    /*Calcula matriz triangular inferior, tamando en cuenta que es una tridiagonal
    simetrica*/

    int i;

    *(w) = *(y);

    for(i = ONE; i < rows; i++)
    {
        *(w + i) = *(y + i) - (*(*(matrix + i - ONE) + ONE)) * (*(w + i - ONE));
    }

}

void solve_calor_diagonal(double **matrix, double *w, int rows, double *z)
{
    /*Calcula resultado de una matriz diagonal*/

    int i;

    for(i = ZERO; i < rows; i++)
    {
        *(z + i) = (*(w + i)) / *(*(matrix + i));

    }

}

void solve_calor_superior(double **matrix, double *z, int rows, double *x)
{
    /*Calcula matriz triangular superior, tamando en cuenta que es una tridiagonal
    simetrica*/

    int i;

    *(x + rows - ONE) = *(z + rows - ONE);

    for(i = rows - TWO; i >= ZERO; i--)
    {
        *(x + i) = *(z + i) - (*(*(matrix + i) + ONE)) * (*(x + i + ONE));
    }

}

double *generar_y(double Q, double K, double d_i, double d_n, int n, double L)
{
    /*Genera el vector y para poder resolver el problema de flujo de calor

    Parametros
    ===========

    double Q: cantidad de energia (calor)
    double K: difusidad termica
    double d_i: condicion de Dirchlet inicial
    double d_n: condicion de Dirchlet final
    int n: el numero de elementos
    double L: la longitud de la barra*/

    int i;
    double value;
    double *y = (double *)calloc(n - ONE, sizeof(double));

    value = Q * (L / n) * (L / n) / K ;

    for(i = ZERO; i < n - ONE; i++)
    {
        *(y + i) = value;
    }

    *(y) += d_i;
    *(y + i - ONE) += d_n;

    return y;
}

double **crear_matriz_calor(int rows)
{
    /*Funcion que crea la estructura general de la matriz de calor
    unicamente necesitamos que el primer termino sea un 2
    los demas valores se generan mediente las ecuaciones que generan
    las matrices que seran factores

    Parametros
    ===========
    int rows: es la dimension de la matriz en filas

    Return
    =======
    Regresa un apuntador double*/

    int i;
    double **matrix = (double**)calloc(rows, sizeof(double*));

    *(matrix) = (double*)calloc(TWO * rows, sizeof(double));

    for(i = ONE; i < rows; i++)
        *(matrix + i) = *(matrix + i - ONE) + TWO;

    /*Necesitamos que el primer elemento sea 2 de aqui se generan las soluciones
    al usar la funcion solve*/
    **matrix = TWO;

    return matrix;
}

void solve_cholesky_calor(double **matrix, int rows, double *y, double *x)
{
    int i;
    double *w = (double *)calloc(rows, sizeof(double));
    double *z = (double *)calloc(rows, sizeof(double));

    /*se aplica la funcion al primer l*/
    *(*(matrix) + ONE) = -1./ (**matrix);

    /*se  aplican las ecuaciones para calcular los elementos de los
    factores y se guardan en la misma matriz*/
    for(i = ONE; i < rows; i++)
    {
        /*matrix_{i} = 2 - l_{i- 1}^{2}d_{i-1}*/
        *(*(matrix + i)) = TWO -\
         (*(*(matrix + i - ONE) + ONE)) * (*(*(matrix + i - ONE) + ONE))\
         * (*(*(matrix + i - ONE)));

        /*l_{i} = \frac{-1}{d_{i}}*/
        *(*(matrix + i) + ONE) = -ONE/ (*(*(matrix + i)));
    }

    /*El ultimo elemento debe ser cero*/
    *(*(matrix + i - ONE) + ONE)  = ZERO;

    solve_calor_inferior(matrix, y, rows, w);
    solve_calor_diagonal(matrix, w, rows, z);
    solve_calor_superior(matrix, z, rows, x);

    free(z);
    free(w);
}

double *solve_calor_diferencias_finitas(double Q, double K, double d_i, double d_n, int n, double L)
{
    /*Resuelve problema de flujo de calor

    Parametros
    ===========

    double Q: cantidad de energia (calor)
    double K: difusidad termica
    double d_i: condicion de Dirchlet inicial
    double d_n: condicion de Dirchlet final
    int n: el numero de elementos si hay 5 nodos hay 4 elementos
    double L: la longitud de la barra*/

    double **matrix, *y;
    double *x = (double *)calloc(n - ONE, sizeof(double));

    int i;

    matrix = crear_matriz_calor(n - ONE);
    y = generar_y(Q, K, d_i, d_n, n, L);
    solve_cholesky_calor(matrix, n - ONE, y, x);

    /*for(i=ZERO; i< n - ONE; i++)
    {
        printf("X%d=%lf,  ", i, *(y + i));

        if((i + ONE)%5 == ZERO)
            printf("\n\n");
    }*/

    printf("\tsolucion para %d elementos\n\n", n);

    for(i=ZERO; i< n - ONE; i++)
    {
        if(i == ZERO)
            printf("X%d=%lf,  ", ZERO, d_i);

        printf("X%d=%lf,  ", i + 1, *(x + i));

        if((i + ONE)%5 == ZERO)
            printf("\n\n");
    }

    printf("X%d=%lf\n", i+1, d_n);


    free(y);
    free(matrix[0]);
    free(matrix);

    return x;
}
