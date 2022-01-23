#ifndef DARRAY
#define DARRAY

double **read_matrix_file(char *, int *, int *, int);
double **read_matrix_file_2(char *, int * , int *);
double *read_array_file(char *, int *);
void print_solucion(double *, int);
void print_diagonal(double **, int, int);
void print_triangular_matrix(double **, int, int, int);
void print_matrix(double **, int, int);
void free_matrix(double **, int);
void free_array(double *);
void print_array(double *, int);
void free_expanded_matrix(double **, int);

#endif /* DARRAY*/
