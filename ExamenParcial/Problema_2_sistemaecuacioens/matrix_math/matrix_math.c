#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#ifndef ZERO
#define ZERO 0
#endif /*ZERO*/

#ifndef ONE
#define ONE 1
#endif /*ONE*/

#ifndef TWO
#define TWO 2
#endif /*TWO*/

int compara_matrices(double **a, double **b, int m, int n, double error)
{
    /*funcion que compara elemento a elemento si dos matrices son 
    similares*/

    int i, j, condition;

    for(i = ZERO; i < m; i++)
    {
        for(j = ZERO; j < n; j++)
        {
            if(fabs(*(*(a + i) + j) - *(*(b + i) + j)) < error)
                condition = ONE; 
            else
                condition = ZERO;
        }
    }

    if(condition)
        return ONE;
    else
        return ZERO;

}

double **traspuesta(double **matrix, int m, int n)
{   
    /*Funcion que realiza la traspuesta de una matriz, 
    regresa una nueva matriz

    int m: es el numero de filas de la matriz original
    int n: es el numero de columnas de la matriz original
    */
   
    int i, j;
    double **tras;

    tras = (double **)malloc(n * sizeof(double * ));
    *tras = (double *)malloc(m * n * sizeof(double));
    
    for (i = ONE; i < n; i++)
        *(tras + i) = *(tras + i - ONE) + m;
    
    for(i = ZERO; i < n; i++)
    {
        for(j = ZERO; j < m; j++)
        {
            *(*(tras + i) + j) = *(*(matrix + j) + i);
        }
    }

    return tras;
}

double **dot_matrix(double **a, double **b, int m, int n, int p, int q)
{
    /*Funcion que realiza el producto punto entre dos matrices,
    la nueva matriz se crea de manera dinamica y debe ser libereda como
    free_matrix(), o free(matrix[0]); free(matrix);
    
    Parametros
    ==========
    double **a: primer matriz, a la izquierda
    double **b: segunda matriz, a la derecha
    int m: filas de la matriz a
    int n: filas de la matriz b
    int p: filas de la matriz p
    int q: filas de la matriz q
    
    Return:
    ========
    Regresa una nueva matriz de dimension mxq c*/

    int i, j, k;
    double **c, sum;
    
    /*la nueva matriz debe de ser de tamanio mxq*/

    c = (double **)malloc(m * sizeof(double *));
    *c = (double *)malloc(m * q * sizeof(double));

    for (i = ONE; i < m; i++)
        *(c + i) = *(c + i - ONE) + q;

    if(n == p)
    {   
        for(i = ZERO; i < m; i++)
        {
            
            for(j = ZERO; j < q; j++)
            {
                sum = ZERO;

                /*realiza la multiplicacion elemento a elemento
                de la fila contra la columna*/
                for(k = ZERO; k < p; k++)
                    sum += (*(*(a + i) + k)) * (*(*(b + k) + j));
                
                *(*(c + i) + j) = sum;
            }
        }
    }
    else
    {
        printf("No se puede multiplicar");
        return NULL;
    }

    return c;

}
double **copy_matrix(double **matrix, int m, int n)
{
    /*Funcion que copia una matriz, la nueva matriz
    es en realidad un arreglo en el que se puede acceder 
    de manera estandar a como se accede una matriz
    
    Parametros
    ==========
    double **matrix: es la matriz que se va a copiar
    int m: son las filas de la matriz
    int n: son las columnas de la matriz*/

    int i, j;
    double **copy;

    copy = (double **)malloc(m * sizeof(double *));
    *copy = (double *)malloc(m * n * sizeof(double));

    for(i = ONE; i < m; i++)
        *(copy + i) = *(copy + i - ONE) + n;

    for(i = ZERO; i < m; i++)
    {
        for(j = ZERO; j < n; j++)
            *(*(copy + i) + j) = *(*(matrix + i) + j);
    }

    return copy;
}

void producto_escalar(double a, double *x, int m)
{
    /*Funcion que multiplica un escalar a un vector
    el resultado se guarda en el vector x*/

    int i;

    for(i = ZERO; i < m; i++)
        (*(x + i)) *= a;
}


void vector_sum(double *x, double *y, int m)
{
    /*funcion que suma elemento a elemento dos vectores,
    el resultado se guardo en el vector x*/

    int i;

    for(i = ZERO; i < m; i++)
    {
        *(x + i) += *(y + i);
    }

}

void vector_rest(double *x, double *y, int m)
{
    /*funcion que resta elemento a elemento dos vectores,
    el resultado se guardo en el vector x*/

    int i;

    for(i = ZERO; i < m; i++)
    {
        (*(x + i)) -= (*(y + i));
    }

}

double dot_vector(double *a, double *b, int m)
{
    /*Realiza el producto punto entre dos vectores*/

    int i;
    double suma = ZERO;

    for(i = ZERO; i < m; i++)
    {
        suma += (*(a + i)) * (*(b + i));
    }

    return suma;
}

void normalizar_vector(double *vector, int m)
{
    /*funcion que normaliza un vector*/

    int i;
    double suma = ZERO;

    /*calcula el denominador*/

    suma = dot_vector(vector, vector, m);

    for(i = ZERO; i < m; i++)
    {
        *(vector + i) /= sqrt(suma);
    }

}

double *dot(double **a, double *b, int m, int n)
{
    /*funcion que realiza el producto punto entre una
    matriz y un vector
    double **a: es la matriz a
    double **b: es la matriz b
    int m: es el numero de filas de la matriz a
    int n: es el numero de columnas de la matriz a y corresponde al
    numero de filas del vector b*/

    double suma;
    int i, j;
    double *result = (double *)calloc(m, sizeof(double));

    for(i = ZERO; i < m; i++)
    {
        suma = ZERO;

        for(j = ZERO; j < n; j++)
        {
            suma += (*(*(a +  i) + j)) * (*(b + j));

        }

         *(result + i) = suma;
    }

    return result;
}

void ortononormalizar(double **vectores, int m, int n)
{
    /*Funcion que ortogonaliza un conjunto de vectores, estos se encuentran
    en una matriz, cada vector forma la fila de la matriz
    asi que se debe de manejar con cuidado, la ortogonalizacion se guarda
    en la misma matriz de entrada*/

    int i, j, k;
    double **temporal, *contribution, factor, denominador;

    /*Existen m vectores de dimension n*/
    temporal = (double **)malloc(m * sizeof(double *));
    *temporal = (double *)malloc(m * n * sizeof(double));

    for (i = ONE; i < m; i++)
        *(temporal + i) = *(temporal + i - ONE) + n;

    /*u1 = v1, asi se inicia gramschmidt*/
    denominador = sqrt(dot_vector(*vectores, *vectores, n));

    for (i = ZERO; i < n; i++)
        *(*temporal + i) = *(*vectores + i)/ denominador;

    for (i = ONE; i < m; i++)
    {
        contribution = (double *)calloc(n, sizeof(double));
        
        for (k = ZERO; k < i; k++)
        {
            factor = dot_vector(*(vectores + i), *(temporal + k), n) /
                     dot_vector(*(temporal + k), *(temporal + k), n);

            for (j = ZERO; j < n; j++)
            {
                *(contribution + j) += factor * *(*(temporal + k) + j);
            }
        }

        for (j = ZERO; j < n; j++)
        {
            *(*(temporal + i) + j) = *(*(vectores + i) + j) - *(contribution + j);
        }

        /*se libera con el fin de reiniciar la variable*/
        free(contribution);
    }

    for (i = ZERO; i < m; i++)
    {
        denominador = sqrt(dot_vector(*(temporal + i), *(temporal + i), n));

        for (j = ZERO; j < n; j++)
            *(*(vectores + i) + j) = *(*(temporal + i) + j) / denominador;
    }

    free(*temporal);
    free(temporal);
}
