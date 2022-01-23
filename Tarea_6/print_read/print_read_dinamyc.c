/*Giovanny Encinia*/
#include <stdio.h>
#include <stdlib.h>
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3

void print_array(double *array, int rows)
{
    int i = ZERO;

    while(i < rows)
    {
        printf("y%d: %lf ", i, *(array + i));
        i++;

        if(i % 5 == ZERO)
            printf("\n");
    }

    printf("\n");


}

void print_solucion(double *array, int rows)
{
    int i = ZERO;

    while(i < rows)
    {
        printf("x%d: %lf ", i, *(array + i));
        i++;

        if(i % 5 == ZERO)
            printf("\n");
    }

    printf("\n");


}

void print_diagonal(double **matrix, int m, int n)
{
    /*Por dentro la matriz esta colapsada en vector
    imprimirlo en dos simensiones es solo para
    una mejor visualzacio*/

    int i = ZERO, j = ZERO;

    while(i < m)
    {
        j = ZERO;

        while(j < m)
        {
            if(i==j)
            {
               printf("%lf ", **(matrix + i));
            }
            else
            {
                printf("%lf ", 0.0);
            }

            j++;
        }

        printf("\n");

        i++;
    }
}

void print_triangular_matrix(double **matrix, int m, int n, int type_matrix)
{


    int i = ZERO, j = ZERO;

    while(i < m)
    {
        j = ZERO;

        while(j < m)
        {
            if((type_matrix==1)?(j >= i): (j <= i))
            {
                printf("%lf ", *(*(matrix + i) + ((type_matrix==1)?(j-i): (j))));
            }
            else
            {
                printf("%lf ", 0.0);
            }

            j++;
        }

        printf("\n");

        i++;
    }
}

void print_matrix(double **matrix, int m, int n)
{
    int i = ZERO, j = ZERO;

    while(i < m)
    {
        j = ZERO;

        while(j < n)
        {
            printf("%lf ", *(*(matrix + i) + j++));
        }

        printf("\n");
        i++;
    }
}

double *read_array_file(char *name, int *m_c)
{
    int i = ZERO, m;

    FILE * file = fopen(name, "r");

    fscanf(file, "%d", &m);

    *m_c = m;

    double *array = (double *)malloc(m * sizeof(double));

    if(array == NULL)
    {
        printf("Memory full");

        return NULL;
    }

    while(i < m)
    {
        fscanf(file, "%lf", array + i++);
    }

    fclose(file);

    return array;
}

double **read_matrix_file(char *name, int *m_c , int *n_c, int type_matrix)
{
    /*
    Crea un arreglo unidimensional que emula una matriz en 2d, es mas rapido
    acceder a los elementos.
    ===========================================================

    1 MATRIZ TRIANGULAR SUPERIOR
    queda desfasada un lugar a la derecha

    123
    045
    006     Ahora para hacer las mismas operaciones pensando
            en que no existe desface se debe de acceder

                        matrix[i][j-i]

                    Valores en el j-i negativos no existen
                    pero estos corresponden  a 0's
    123
    450
    600

    ============================================================

    2 MATRIZ DIAGONAL
    La matriz se colapsa en una sola columna

    100
    020
    003
            La funcion regresa un doble apuntador por lo que
            tenemos una matriz de m*1, podemos acceder facilmente
            a los elementos teniendo esto en cuenta.
    1
    2
    3

    ==============================================================

    3 MATRIZ TRIANGULAR INFERIOR
    La matriz se accede de la misma manera que siempre, pero
    hay que considerar que no se puede acceder a los intervalos
    de los ceros, ya que no se asigno memoria a los 0's

    ==============================================================

    Otro Matrices de cualquier tipo
    Se lee y guarda la matriz de una manera estandar
    se puede acceder a lamatriz como en cualquier otro
    arreglo bidimencional

    */

    int i = ONE, j = ZERO, m, n, factor = 0, gap = 0;
    double value;

    FILE* file = fopen(name, "r");

    fscanf(file, "%d %d", &m, &n);

    *m_c = m;
    *n_c = n;

    double **matrix = (double**)malloc(m * sizeof(double*));

    if(matrix == NULL)
    {
        printf("Memory full");

        return NULL;
    }

    /*find exact memory for data in different types of matrixes*/
    switch(type_matrix)
    {
    case ONE: /*superior triangular*/
        factor = (m * n - (m * (m - ONE))/TWO);
        break;
    case THREE: /*inferior triangular*/
        factor = (m * n - (m * (m - ONE))/TWO);
        break;
    case TWO: /*diagonal*/
        factor = m;
        break;
    default: /*normal*/
        factor = m * n;
    }

    *(matrix) = (double*)malloc(factor * sizeof(double));

    /*divide in blocks , analogue to rows*/
    while(i < m)
    {

        switch(type_matrix)
        {
        case ONE: /*superior triangular*/
            gap = n - i + ONE;
            break;
        case TWO: /*diagonal*/
            gap = ONE;
            break;
        case THREE: /*inferior triangular*/
            gap = i;
            break;
        default: /*normal*/
            gap = n;
        }

        *(matrix + i) = *(matrix + i - ONE) + gap;
        i++;
    }

    i = ZERO;

    /*Read and save the data in dynamic memory*/
    while(i < m)
    {

        j = ZERO;

        while(j < n)
        {
            fscanf(file, "%lf", &value);

            if(type_matrix <= THREE && type_matrix > ZERO)
            {

                if(value != ZERO)
                {

                    switch(type_matrix)
                    {
                    case ONE:/*Superior*/
                        gap = j - i;
                        break;
                    case TWO:/*diagonal*/
                        gap =ZERO;
                        break;
                    default:/*inferior*/
                        gap = j;
                    }

                    *(*(matrix + i) + gap) =  value;

                }
            }
            else
            {
                *(*(matrix + i) + j) =  value;
            }

            j++;
        }

        i++;
    }

    fclose(file);

    return matrix;
}

double **read_matrix_file_2(char *name, int *m_c , int *n_c)
{
        /*Esta funcion lee los datos de un archivo de texto y crea
        un arreglo dinamico en dos dimensiones, esta funcion esta pensada
        para poder usarse cuando se requieran arreglos bidimensionales
        tal es el caso de el metodo de Gauss con pivoteo total
        Contiene una columna extra donde se almacenan las Y
        */

        int i = ZERO, j = ZERO, m, n;
        FILE* file = fopen(name, "r");

        fscanf(file, "%d %d", &m, &n);

        *m_c = m;
        *n_c = n;

        double **matrix = (double**)malloc(m * (n+1) * sizeof(double*));

        if(matrix == NULL)
        {
            printf("Memory full");

            return NULL;
        }

        while(i < m)
        {
            *(matrix + i) = (double*)malloc((n+1) * sizeof(double));
            i++;
        }

        i = ZERO;

        while(i < m)
        {
            j = ZERO;

            while(j < n)
            {
                fscanf(file, "%lf", (*(matrix + i) + j));
                j++;
            }

            i++;
        }

        return matrix;
}

void free_expanded_matrix(double **matrix, int rows)
{
    int i;

    for(i = ZERO; i < rows; i++)
    {
       free(*(matrix + i));
    }

    free(matrix);
}

void free_matrix(double **matrix, int rows)
{
    free(matrix[ZERO]);
    free(matrix);
}

void free_array(double *ar)
{
    free(ar);
}
