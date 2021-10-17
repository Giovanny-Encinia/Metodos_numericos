#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../eigen_jacobi/eigen_jacobi.h"
#include "../potencia_inversa/potencia_inversa.h"
#include "../matrix_math/matrix_math.h"
#include "../print_read/prdynamic.h"
#define ERROR 1E-10
#define LIMITE 2000

double **subespacio(double **matrix, int m, int number_eigen, double **eigen_valores_)
{
    int i, j, condition = ONE, number, iteration = ZERO;
    double **eigenvectores, **eigen_temp, **eigen_traspuesta;
    double *evalues, **Q, **Q_t, **LU, **Qtemp, **eigen_valores;
    double **der, **izq;

    eigen_traspuesta = NULL;

    while(condition && iteration < LIMITE)
    {
        /*los eigenvectores estan por filas,
        es como si regresara el resultado como una traspuesta*/
        LU = copy_matrix(matrix, m, m);
        eigen_traspuesta = eigen_menores(LU, m, m, &number, evalues, number_eigen, ONE, eigen_traspuesta);
        /*se libera memoria de los eigenvalores ya que no se necesitan aun*/
        /*realiza el producto de \Phi^{T} * A*/
        ortononormalizar(eigen_traspuesta, number_eigen, m);
        eigen_temp = dot_matrix(eigen_traspuesta, matrix, number_eigen, m, m, m);
        /*regresa a normalidad la traspuesta*/
        eigenvectores = traspuesta(eigen_traspuesta, number_eigen, m);
        /*con base a la teoria, este seria nuestra matriz B*/
        eigen_valores = dot_matrix(eigen_temp, eigenvectores, number_eigen, m, m, number_eigen);
        /*se libera la memoria de variables auxiliares*/
        
        free(eigen_temp[0]);
        free(eigen_temp);
        
        /*Se trata de diagonalizar la matriz B: eigen_valores*/
        Q = eigen_jacobi(eigen_valores, number_eigen);

        /*Se revisa que la matriz se halla diagonalizado*/
        for (i = ZERO; i < number_eigen; i++)
        {
            for (j = ZERO; j < number_eigen; j++)
            {
                if (i != j)
                {
                    if (fabs(*(*(eigen_valores + i) + j)) < ERROR)
                        condition = ZERO;
                    else
                        condition += ONE;
                }
            }
        }

        /*la matriz ha sido diagonalizada, termina el ciclo*/
        if (!condition || iteration >= LIMITE - ONE)
            break;

        free(eigen_valores[0]);
        free(eigen_valores);
        
        Q_t = traspuesta(Q, number_eigen, number_eigen);
        /*con esto se actualizara el nuevo vector*/
        Qtemp = dot_matrix(Q_t, eigen_traspuesta, number_eigen, number_eigen, number_eigen, m);
        free(Q[0]);
        free(Q);
        
        free(Q_t[0]);
        free(Q_t);
        
        /*se actualiza el valor del eigenvector, una mejor
        aproximacion*/
        for(i = ZERO; i < number_eigen; i++)
        {
            for(j = ZERO; j < m; j++)
                *(*(eigen_traspuesta + i) + j) = *(*(Qtemp + i) + j);
        }

        free(Qtemp[0]);
        free(Qtemp);
        iteration++;
    }

    printf("El numero de iteraciones es: %d\n", iteration + ONE);
    /*se copian los elementos de los eigenvalores*/
    for(i = ZERO; i < number_eigen; i++)
    {
        for(j = ZERO; j < number_eigen; j++)
            *(*(eigen_valores_ + i) + j) = *(*(eigen_valores + i) + j);
    }

    free(eigen_traspuesta[0]);
    free(eigen_traspuesta);
    free(eigen_valores[0]);
    free(eigen_valores);

    return eigenvectores;
}