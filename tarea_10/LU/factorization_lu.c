#include <stdio.h>
#include <stdlib.h>
#define ZERO 0
#define ONE 1

/*Contiene factorizacion por LU y solucion a matrices cuadradas por LU*/
double sumatoria_triangulares(double **matrix,  double *x, int i, \
  int n, int begin, int end)
{
    /*simple sumatoria, en otros programas se repite la misma funcion
    se debe de buscar una manera de no repetir codigo*/
    double sum = ZERO;
    int j = begin;

    while(j <= end)
    {
        sum += (*(*(matrix+i) + j)) * (*(x + j));
        j++;
    }

        return sum;

}

double sumatoria_f(double **matrix, int m, int i, int j)
{
    /*Dado que las dos matrices L y U se guardan
    en la matriz original, se debe de tratar de una manera particular
    dicha matriz, es  por eso la vreacion de esta funion, es necesario saber
    las coordenadas i y j para saber que operaciones hacer*/

    double sum = ZERO;
    int k = ZERO, condition;

    if(i < j)
        condition = i;
    else
        condition = j;


    while(k <= condition - ONE)
    {
        /*simula el elemento de la diagonal
        en la matriz U*/
        if(k == i)
        {
            sum += (*(*(matrix+i) + k));
        }
        else
        {
            sum += (*(*(matrix+i) + k)) * (*(*(matrix + k) + j));
        }

        k++;
    }

        return sum;
}

void triangular_super_lu(double **matrix, int rows, double *x, double *y)
{
    /*simplemente se aplica el metodo para
    solucionar una matriz triangula superior, pero se
    realiza una ligera modificacion, ya que L y U se alojan
    en la matriz original, solo se debe tener en cuenta que
    los elementos de la diagonal de U son 1*/

    int i = ZERO;
    int n = rows-ONE;

    /*el ultimo termino es rows-ONE*/
    *(x + n) = *(y + n);
    i = n - ONE;

    while(i >= 0)
    {
        /*se raliza una ligera modificacion ya que los elementos
        de la matriz superior son igual a 1*/
        *(x + i) =  *(y+ i) - sumatoria_triangulares(matrix, x, i, rows, i + ONE, n);
        i--;
    }

}

void triangular_infer_lu(double **matrix, int rows, double *x, double *y)
{
    /*
    i = {1, 2, ..., n}
    xi = \frac{1}{matriz[i][i]} * (yi - \sum_{j = 1}^{i}matrix[i][j]*x[j])
    exactamente el mismo metodo de siempre*/

    int i = ZERO;

    /*el ultimo termino es rows-ONE*/
    *(x) = *(y)/ (*(*(matrix)));

    i = ONE;

    while(i < rows)
    {
        *(x + i) =  ((*(y + i)) - sumatoria_triangulares(matrix, x, i,rows, ZERO, i - ONE)) / *(*(matrix+i) + i);
        i++;
    }

}

int factorization_lu(double **matrix, int m, double *x, double *y)
{
    /*metodo de estandar para la factorizacion
    se utiliza el metodo de Crout*/
    int i, j;

    for(i = ZERO; i < m; i++ )
    {
        for(j = ONE; j < m; j++)
        {
            if(i == ZERO)
            {
                *(*(matrix + i) + j) /= **matrix;
            }
            else
            {
                /*L_{i, j}*/
                if(i >= j)
                {
                    *(*(matrix + i) + j) -= sumatoria_f(matrix, m, i, j);

                    if(i == j && *(*(matrix + i) + j)  == 0.)
                    {
                        printf("Hay un cero en la diagonal, DIVERGE\n");
                        j += m + ONE;
                        i += m + ONE;
                    }

                }

                /*U_{i, j}*/
                if(i < j)
                    *(*(matrix + i) + j) = (*(*(matrix + i) + j)\
                    - sumatoria_f(matrix, m, i, j))/ (*(*(matrix + i) + i)) ;

            }

        }
    }

    if(i > m + ONE)
        return ZERO;

    return ONE;
}

int solve_lu(double **matrix, int m, double *x, double *y, int factorizada)
{
    /*funcion que resuelve un sistema matricial con factorizacion LU,
    L(y_p) = y; U(x) = y_p
    x es el valor que se debe de tomar como respuesta*/

    int success = ONE;
    double *y_p = (double *)malloc(m * sizeof(double));

    /*la matriz no esta factorizada, se debe factorizar*/
    /*sucede si se utiliza la matriz LU muchas veces*/
    if(!factorizada)
        success = factorization_lu(matrix, m, x, y);


    if(success)
    {
        /*nuesta x para solucionar la primera parte del metodo
        sera y_p, y esta sera nuestra y al resolver la triangular
        superior*/
        triangular_infer_lu(matrix, m, y_p, y);
        triangular_super_lu(matrix, m, x, y_p);
        free(y_p);

        return ONE;
    }
    else
    {
        free(y_p);
        return ZERO;
    }

}
