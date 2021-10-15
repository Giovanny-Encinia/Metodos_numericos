#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../eigen_jacobi/eigen_jacobi.h"
#include "../potencia_inversa/potencia_inversa.h"
#include "../matrix_math/matrix_math.h"
#include "../print_read/prdynamic.h"
#define ERROR 1E-11

double **subespacio(double **matrix, int m, int number_eigen, double **eigen_valores)
{
    int i, j, condition = 1, number;
    double **eigenvectores, **eigen_temp, **eigen_traspuesta;
    double *evalues, **Q, **Q_t, **LU;

    eigen_traspuesta = NULL;

    while(condition)
    {
        
        /*los eigenvectores estan por filas,
        es como si regresara el resultado como una traspuesta*/
        LU = copy_matrix(matrix, m, m);
        eigen_traspuesta = eigen_menores(LU, m, m, &number, evalues, number_eigen, ONE, eigen_traspuesta);
        /*se libera memoria de los eigenvalores ya que no se necesitan aun*/
        /*realiza el producto de \Phi^{T} * A*/
        eigen_temp = dot_matrix(eigen_traspuesta, matrix, number_eigen, m, m, m);
        /*regresa a normalidad la traspuesta*/
        eigenvectores = traspuesta(eigen_traspuesta, number_eigen, m);
        /*con base a la teoria, este seria nuestra matriz B*/
        eigen_valores = dot_matrix(eigen_temp, eigenvectores, number_eigen, m, m, number_eigen);
        /*se libera la memoria de variables auxiliares*/
        
        free(eigen_temp[0]);
        free(eigen_temp);
        
        /*Se revisa que la matriz se halla diagonalizado*/
        for(i = ZERO; i < number_eigen; i++)
        {
            for(j = ZERO; j < number_eigen; j++)
            {
                if(i != j)
                {
                    if(fabs(*(*(eigen_valores + i) + j)) < ERROR)
                        condition = ZERO;
                    else
                        condition = ONE;
                }
            }

        }

        /*la matriz ha sido diagonalizada, termina el ciclo*/
        if(!condition)
            break;
        
        Q = eigen_jacobi(eigen_valores, number_eigen);
        Q_t = traspuesta(Q, m, m);
        /*!!!!aqui hay un problema de segmentacion*/
        eigen_temp = dot_matrix(Q_t, eigen_traspuesta, number_eigen, m, m, m);
        printf("funciona\n");
        free(Q_t[0]);
        free(Q_t);

        for(i = ZERO; i < number_eigen; i++)
        {
            for(j = ZERO; j < m; j++)
                *(*(eigen_traspuesta + i) + j) = *(*(eigen_temp + i) + j);
        }

        free(eigen_temp[0]);
        free(eigen_temp);
    }

    print_matrix(eigen_valores, number_eigen, number_eigen);

    free(eigen_valores[0]);
    free(eigen_valores);
    free(eigen_traspuesta[0]);
    free(eigen_traspuesta);

    return eigenvectores;
}