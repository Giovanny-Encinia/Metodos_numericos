#ifndef MATRIX_MATH
#define MATRIX_MATH

#ifndef ZERO
#define ZERO 0
#endif /*ZERO*/

#ifndef ONE
#define ONE 1
#endif /*ONE*/

#ifndef TWO
#define TWO 2
#endif /*TWO*/
double norma(double *vector, int m);
double **matrix_zero(int m, int n);
void ortononormalizar(double **vectores, int m, int n);
int compara_matrices(double **a, double **b, int m, int n, double error);
double **traspuesta(double **matrix, int m, int n);
void producto_escalar(double a, double *x, int m);
void vector_rest(double *x, double *y, int m);
void vector_sum(double *x, double *y, int m);
void normalizar_vector(double *vector, int m);
double dot_vector(double *a, double *b, int m);
double *dot(double **a, double *b, int m, int n);
double **copy_matrix(double **matrix, int m, int n);
double **dot_matrix(double **a, double **b, int m, int n, int p, int q);
#endif // MATRIX_MATH
