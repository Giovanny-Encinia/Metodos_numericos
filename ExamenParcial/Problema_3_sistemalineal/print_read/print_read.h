#ifndef PRINTREAD_H
#define PRINTREAD_H
void imprime_solucion(char *name, double *x, int m);
int es_diagonal(char *name);
double **leer_examen_seidel(char *name, int*, int*);
double **leer_examen_diagonal(char *name, int *m_c);
double *read_vector(char *name);
void print_matrix(double **matrix, int m);
double **leer_matrix_gauss(char *name, int *m_c);
#endif