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
void producto_escalar(double a, double *x, int m);
void vector_rest(double *x, double *y, int m);
void vector_sum(double *x, double *y, int m);
void normalizar_vector(double *vector, int m);
double dot_vector(double *a, double *b, int m);
double *dot(double **a, double *b, int m, int n);
#endif // MATRIX_MATH
