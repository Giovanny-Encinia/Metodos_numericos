#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../print_read/prdynamic.h"
#ifndef ZERO
#define ZERO 0
#endif /* ZERO*/
#ifndef ONE
#define ONE 1
#endif /* ONE*/
#ifndef ERROR
#define ERROR 1E-18
#endif // ERROR
#ifndef MPI
#define MPI 3.14159265358979323846
#endif

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

    mayor = fabs(*(*(matrix) + ONE));

    for(k = ZERO; k < m; k++)
    {
        for(l = ZERO; l < m ; l++)
        {
            /*ignoramos los elementos de la diagonal*/
            if(k != l)
            {
                if(fabs(*(*(matrix + k) + l)) >= mayor)
                {
                    /*los indices correspoonden al elemento mas cercano
                    a la primera fila*/
                    *i = l;
                    *j = k;
                    mayor = fabs(*(*(matrix + k) + l));
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

    int i, j, k, l, r, iteration = ZERO;
    double theta, **eigenvectores, cik, cjk, cii, cjj;
    double s, c, s2, c2, numerador, denominador, cij, eli, elj;

    /*se pide memoria para la matriz que contendra los eigenvectores*/
    eigenvectores = (double **)calloc(m, sizeof(double *));
    *eigenvectores = (double*)calloc(m * m, sizeof(double));

    /*matriz guardada en forma de vector*/
    for(r = ONE; r < m; r++)
        *(eigenvectores + r) = *(eigenvectores + r - ONE) + m;

    /*se buscan los indices del elemento mayor absoluto*/
    mayor_absoluto(matrix, m, &i, &j);

    while(fabs(*(*(matrix + i) + j)) > ERROR)
    {
        /*Calculo del angulo*/
        numerador = (*(*(matrix + i) + j)) * 2.;
        denominador = (*(*(matrix + i) + i)) -  (*(*(matrix + j) + j));

        /*si matrix_{ii} = matrix_{j,j} theta es pi/4*/
        if(denominador < 1E-11)
            theta = MPI / 4.;
        else
            theta = atan(numerador / denominador) * 0.5;

        /*se calculan las funciones senoidales necesarias*/
        s = sin(theta);
        c = cos(theta);
        s2 = s * s;
        c2 = c * c;

        /*cii*/
        cii = (*(*(matrix + i) + i)) * c2 + 2. * (*(*(matrix + i) + j)) * s * c + (*(*(matrix + j) + j)) * s2;
        /*cjj*/
        cjj = (*(*(matrix + i) + i)) * s2 - 2. * (*(*(matrix + i) + j)) * s * c + (*(*(matrix + j) + j)) * c2;
        /*cij*/
        cij = ((*(*(matrix + j) + j)) - (*(*(matrix + i) + i))) * s * c +\
        (*(*(matrix + i) + j)) * (c2 - s2);
        *(*(matrix + i) + j) = *(*(matrix + j) + i) = cij;
        *(*(matrix + j) + j) = cjj;
        *(*(matrix + i) + i) = cii;



        /*con base a lo encontrado en la teoria, esto afecta a filas i, j
        esto es para actualizar elementos de la nueva matriz*/
        for(k = ZERO; k < m; k++)
        {

            if(k != i && k != j)
            {
                /*ecuaciones encontradas mediante la teoria*/
                cik = (*(*(matrix + i) + k)) * c + (*(*(matrix + j) + k)) * s;
                cjk = -(*(*(matrix + i) + k)) * s + (*(*(matrix + j) + k)) * c;

                (*(*(matrix + i) + k)) = (*(*(matrix + k) + i)) = cik;
                (*(*(matrix + j) + k)) = (*(*(matrix + k) + j)) = cjk;
            }

        }

        /*aqui se realizan los calculos de la matriz con eigenvectores
        con cada iteracion esta se actualiza*/
        /*si es la primera iteration nuestra primera aproximacion, simplemente
        sera la primera matriz de rotacion*/
        if(iteration == ZERO)
        {
            /*1's en la diagonal*/
            for(l = ZERO; l < m; l++)
            {

                for(k = ZERO; k < m; k++)
                {
                    if(l == k)
                        *(*(eigenvectores + l) + k) = ONE;
                }

             }

             /*se agregan valores para crear la matriz de rotacion*/
             *(*(eigenvectores + i) + i) = *(*(eigenvectores + j) + j) = c;
             *(*(eigenvectores + i) + j) = -s;
             *(*(eigenvectores + j) + i) = s;
        }
        else
        {

            /*si no estamos en la primera iteracion entonces se calcula de la
            siguiente manera la matriz con eigenvectores*/
            for(l = ZERO; l < m; l++)
            {
                eli = (*(*(eigenvectores + l) + i)) * c + (*(*(eigenvectores + l) + j)) * s;
                elj =  -(*(*(eigenvectores + l) + i)) * s + (*(*(eigenvectores + l) + j)) * c;
                *(*(eigenvectores + l) + i) = eli;
                *(*(eigenvectores + l) + j) = elj;
            }

        }

        /*se buscan los indices del nuevo mayor valor absoluto*/
        mayor_absoluto(matrix, m, &i, &j);
        iteration++;
    }

    printf("El numero de iteraciones es: %d\n", iteration);
    return eigenvectores;
}
