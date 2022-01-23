#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../matrix_math/matrix_math.h"
#include "../print_read/prdynamic.h"
#ifndef ONE
#define ONE 1
#endif /*ONE*/
#ifndef ZERO
#define ZERO 0
#endif /*ZERO*/
#ifndef ERROR
#define ERROR 1E-13
#endif /*ERROR*/

void rayleigh_eigen(double **matrix, int m, double *eigenvalor, double *eigenvector)
{
    /*Funcion que calcula eigenpar de una matriz, este metodo se debe de 
    utilizar con cuidado ya que no se asegura su convergencia
    
    Parametros
    ===========
    double **matrix: es la matriz de la que se obtendra el eigenpar
    int m: es la dimension de la matriz
    double *eigenvalor: es la aproximacion al eigenvalor, este se ira actualizando
    double *eigenvector: es la aproximacion al eigenvector, se ira actualizando*/

    int i, j, condition = ONE, iterations = ZERO;
    double valor_t, *residuo, *eigenvector_n;
    
    residuo = (double *)calloc(m, sizeof(double));

    while(condition && iterations < 1000)
    {
        /*Este servira despues como el nuevo eigenvector inicial
        es decir una nueva aproximacion, ademas se utiliza en la definicion
        del metodo*/
        
        eigenvector_n = dot(matrix, eigenvector, m, m);
        /*se calcula el vector residuo*/
        for(j = ZERO; j < m; j++)
        {
            *(residuo + j) = (*(eigenvector_n + j))\
            - (*eigenvalor) * (*(eigenvector + j));
        }

        /*se  guarda el eigenvalor, ya que se  utilizara despues para
        la condicion de convergencia*/
        valor_t = *eigenvalor;
        /*se aplica la transformacion que acerca al valor del 
        eigenvalor*/
        *eigenvalor = valor_t +
                      dot_vector(eigenvector, residuo, m) /\
                      dot_vector(eigenvector, eigenvector, m);

        /*si el nuevo eigenvalor es igual al anterior
        entonces se ha encontrado la respuesta*/
        if(fabs(*eigenvalor - valor_t) < ERROR)
        {
            condition = ZERO;
        }
        else
        {
            /*no se ha encontrado la respuesta, entonces actualiza
            el nuevo eigenvector Axo = x1*/
            for(j=ZERO; j < m; j++)
                *(eigenvector + j) *= (*eigenvalor);

        }
        
        iterations++;
        /*libera memoria*/
        free(eigenvector_n);
    }

    printf("El numero de iteraciones es: %d\n", iterations);
    
    /*libera la memoria de residuo*/
    free(residuo);

}