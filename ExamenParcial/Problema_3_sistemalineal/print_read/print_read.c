#include <stdlib.h>
#include <stdio.h>

void print_matrix(double **matrix, int m)
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < m; j++)
            printf("%lf ", *(*(matrix + i) + j));
        
        printf("\n");
    }

}

void imprime_solucion(char *name, double *x, int m)
{
    FILE *file;
    int i, j;

    file = fopen(name, "w");

    fprintf(file, "%d 1\n", m);

    for(i = 0; i < m; i++)
    {
        fprintf(file, "%.14lf\n", *(x + i));
    }

    printf("La solucion se ha guardado en %s\n", name);
    fclose(file);

}

int es_diagonal(char *name)
{
    FILE *file;
    int m, n, i, j, k, l;
    float value;

    file = fopen(name, "r");

    fscanf(file, "%d %d %d", &m, &n, &j);

    for (i = 0; i < m; i++)
    {
        fscanf(file, "%d%d%f", &k, &l, &value);

        if(k != l)
        {
            printf("No es diagonal: i %d, j %d\n", k, l);
            fclose(file);

            return 0;
        }

    }

    printf("Es diagonal\n");
    fclose(file);

    return 1;

}

double *read_vector(char *name)
{
    FILE *file;
    int m, n, i, j, k, l;
    double *vector;

    file = fopen(name, "r");

    fscanf(file, "%d %d", &m, &n);
    vector = (double *)calloc(m, sizeof(double ));

    for(i = 0; i < m; i++)
    {
        fscanf(file, " %lf", (vector + i));
    }

    return vector;

}

double **leer_examen_diagonal(char *name, int *m_c)
{
    FILE *file;
    int m, n, i, j, k, l;
    double **matrix;

    file = fopen(name, "r");

    fscanf(file, "%d %d %d", &m, &n, &j);
    matrix = (double **)calloc(m, sizeof(double *));
    *matrix = (double *)calloc(m, sizeof(double *));
    
    for (i = 1; i < m; i++)
        *(matrix + i) = *(matrix + i - 1) + 1;

    for (i = 0; i < m; i++)
    {
        fscanf(file, "%d %d %lf", &k, &l, (*(matrix + i)));
    }

    *m_c = m;
    
    return matrix;
}

double **leer_examen_seidel(char *name, int *m_c, int *n_c)
{
    FILE *file;
    int m, n, i, j, k, l;
    double **matrix;

    file = fopen(name, "r");

    fscanf(file, "%d %d %d", &m, &n, &j);
    matrix = (double **)calloc(m, sizeof(double *));
    *matrix = (double *)calloc(m * m, sizeof(double));

    for (i = 1; i < m; i++)
        *(matrix + i) = *(matrix + i - 1) + m;

    for (i = 0; i < m; i++)
    {
        fscanf(file, "%d %d %lf", &k, &l, (*(matrix + i) + i));
    }

    *m_c = m;
    *n_c = n;

    return matrix;
}

double **leer_matrix_gauss(char *name, int *m_c)
{
    FILE *file;
    int m, n, i, j, k, l;
    double **matrix;

    file = fopen(name, "r");
    
    fscanf(file, "%d %d %d", &m, &n, &j);
    matrix = (double **)calloc(m, sizeof(double *));
    
    for (i = 0; i < m; i++)
        *(matrix + i) = (double *)calloc(m, sizeof(double));
    
    for (i = 0; i < m; i++)
    {
        fscanf(file, "%d %d %lf", &k, &l, (*(matrix + i) + i));
    }

    *m_c = m;
    fclose(file);
    return matrix;
}