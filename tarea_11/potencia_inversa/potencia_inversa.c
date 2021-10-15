#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../print_read/prdynamic.h"
#include "../matrix_math/matrix_math.h"
#include "../LU/factorization_lu.h"
#ifndef ZERO
#define ZERO 0
#endif /*ZERO*/

#ifndef ONE
#define ONE 1
#endif /*ONE*/

#ifndef TWO
#define TWO 2
#endif /*TWO*/
#define LIMIT 1000000
#define ERROR 1E-13

void free_solution_eigen_(double **solution)
{
    /*Funcion que ayuda a liberar la memoria
    creada para almacenar la matriz que contiene
    los eigenpares*/

    free(*(solution));
    free(*(solution + ONE));
    free(solution);
}

double **eigen_menor(double **matrix, int m, double **eigen_old , int k, int subespacio)
{
    /*Calcula el eigenvalor y eigen vector menor de
    una matriz

    Parametros
    ===========
    double **matrix: matriz de la que queremos obtner los eigenpares
    int m: es la dimension de la matriz
    double **eigen_old: es una variable que guarda los eigenvectores
    int k: esta variable nos indica el indice del eigenpar que estamos
    calculando y ayuda como variabla auxiliar a que el algoritmo funcione

    Return
    =======
    double **sol: es una matriz que contiene en su primera fila el eigenvalor
    y en su segunda fila contiene el eigenvector
    */

    double ai;
    double *x1, *x0, lambda_old = 4000000;
    /*se almacena el eigenvalor y eigenvector*/
    /*El primer elemento sera el eigenvalor*/
    /*sol es una matriz que contiene los eigen pares*/
    double **sol = (double **)malloc(TWO * sizeof(double *));
    double numerador, denominador;
    int iteration = ZERO, value, i, j;
    
    /*el primer elemento de la matriz sol contiene el eigenvalor*/
    *sol = (double*)malloc(sizeof(double));
    *(sol + ONE) = (double*)malloc(m * sizeof(double));
    /*Se crea espacio para el vector inicial*/
    x0 = (double*)calloc(m, sizeof(double));
    
    if(subespacio)
    {/*Aqui hay un problema segmentacion!!!!!*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = *(*(eigen_old + k) + i);

    }
    else
    {
        /*el primer vectopr inicial del primer eigenvalor(el menor)
        se inicializa como 1/sqrt(m)*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = ONE/sqrt(m);
    }
    x1 = (double *)calloc(m, sizeof(double));
    
    while(iteration < LIMIT)
    {

        /*aqui se quitan los terminos anteriores
        de los eigenvectores*/
        if(k)
        {

            for(i = ZERO; i < k; i++)
            {
                /*es el producto punto de el eigenvector traspuesto
                y el x0*/
                ai = dot_vector(*(eigen_old + i), x0, m);

                /*a cada elemento del vactor se le resta an*eigen_valor_{i}*/
                for(j = ZERO; j < m; j++)
                    *(x0 + j) -= (ai * (*(*(eigen_old + i) + j)));

            }

        }


        /*calcula el valor del nuevo vector con x0 = A^{-1}x1*/

        /*el nuevo vector es x1 y value se usa para saber si se realizo
        correctamente la factorizacion*/

        /*el atributo iteration + k es de suma imporrtancia,
        cuando este es cero se factoriza LU y se gusrda en la matriz, cuando este es
        diferente de cero, ya no necesita factorizar y utiliza el LU encontrado por
        primera vez, en x1 se guarda el resultado*/
        value = solve_lu(matrix, m, x1, x0, iteration + k);


        if(!value)
            printf("No se puede factorizar\n");

        /*calcula el valor de lambda x1^{T}x0/ x0^{T}x0*/
        numerador = dot_vector(x0, x0, m);
        denominador = dot_vector(x1, x0, m);

        /*es el nuevo valor del eigenvalor*/
        **(sol) = numerador / denominador;

        /*identifica cuando converge al eigenvalor dominante*/
        if(fabs(lambda_old - (**sol)) < ERROR)
        {
            /*se guarda el eigenvector*/
            /*memoria en x1 se elimina al eliminar memoria de sol*/

            normalizar_vector(x1, m);

            for(i = ZERO; i < m; i++)
                *(*(sol + ONE) + i) = *(x1 + i);

            free(x1);
            /*liberamos la memoria de x0*/
            free(x0);
            /*liberamos la matriz que se aha creado*/
            
            return sol;
        }
        
        /*se actualiza lammbda old*/

        lambda_old = **(sol);

        /*se actualiza el vector inicial*/
        for(i = ZERO; i < m; i++)
            *(x0 + i) = *(x1 + i);

        normalizar_vector(x0, m);

        /*es necesario normalizar para que los elementos
        de los vectores no sean demasiados
        grandes*/
        iteration++;

        /*Para el metodo de iteracion en subespacio
        solamente necesitamos la primera iteracion*/
        if(subespacio)
        {
            for (i = ZERO; i < m; i++)
                *(*(sol + ONE) + i) = *(x1 + i);
            
            free(x1);
            free(x0);
            return sol;
        }
    }

    free(x0);
    printf("No se puede encontrar la solucion\n");

    return NULL;
}

double **eigen_menores(double **matrix, int m, int n, int *number, double *eigen_valores, int m_eigen, int subespacio, double **eigenvectores)
{

    /*Funcion que puede se vista de manera auxiliar, lo mas importante es el ciclo que hay,
    y el como se guardan los datos, esta estructura de la funcion es para
    poder obtener los m eigenpares menores de una matriz mediante deflacion
    usando el metodo de la potencia inversa
    m_eigen son los m eigenvalores*/

    int i, j, number_eigen;
    double **sol, **eigen_old, *eigen_values;
    /*archivo Resultados/Materiales/....txt*/
    
    number_eigen = m_eigen;
    *number = number_eigen + ONE;
    /*se crea memoria para los eigenvectores*/
    /*el primer elemento de los eigenvectores
    sera el vector 0, asi que se debe tener cuidado*/
    
    if(eigenvectores == NULL)
    {
        
        eigen_old = (double **)calloc((number_eigen) * m , sizeof(double *));
        
        for(i = ZERO; i < number_eigen; i++)
            *(eigen_old + i) = (double *)calloc(m, sizeof(double));

        /*para el metodo del subespacio se necesitan
        vectores iniciales ortgonales*/
        for(i = ZERO; i < number_eigen; i++)
            *(*(eigen_old + i) + i) = ONE;
    }
    else
        eigen_old = eigenvectores;
    
    eigen_values = (double *)malloc((number_eigen) * m * sizeof(double));

    
    for(i = ZERO; i < number_eigen; i++)
    {
        /*se encuentra el eigenpar*/
        sol = eigen_menor(matrix, m, eigen_old, i, subespacio);
        
        /*imprime en pantalla solo si se el resultado que
        se dara es pequenio*/
        if(m < 8 && !subespacio)
        {
            printf("|Eigen Menor %5d %59s\n", i,"|");
            printf("------------------------");
            printf("-------------------------------------------------------\n");
            /*posicion cero tiene un eigenvalor*/
            /*0 eigenvalor
            1  {1, 1, 1, 1,...m}*/
            printf("Eigenvalor: %lf\n", **sol);
            printf("|Eigen Valor %5d %59s\n", i,"|");
            /*solucion uno corresponde a un eigenvector*/
            print_solucion(*(sol + ONE), m);
            printf("========================");
            printf("=======================================================\n");
            printf("\n");
        }
        else
            printf("calculando eigenvalores...\n");

        /*pide memoria para separar eigenvalores y
        eigenvectores*/
        *(eigen_values + i) = **sol;

        /*se pasa la solucion a memoria que se pide de una
        funcion externa*/
        for(j = ZERO; j < m; j++)
           *(*(eigen_old + i) + j) =  *(*(sol + ONE) + j);
        
        /*sol se crea de manera recurrente con cada eigenpar encontrado
        asi que se debe de eliminar*/
        free_solution_eigen_(sol);
        
    }

    /*se guarda la solucion en mmoriia creada desde una funcion externa*/
    if(!subespacio)
    {
        for(i = ZERO; i < number_eigen; i++)
            *(eigen_valores + i) = *(eigen_values + i);

    }
    
    /*se elimina la memoria dinamica*/
    free_matrix(matrix, m);
    free(eigen_values);

    printf("Proceso terminado con exito>>>>>>>>>>>>\n");
    return eigen_old;
}
