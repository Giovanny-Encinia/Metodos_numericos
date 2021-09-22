#ifndef JACOBIH
#define JACOBIH
void solve_jacobi(char *name_mat, char *name_vec, double error);
int convergencia(double **matrix, int rows, double *x, double *y, double error);
void jacobi(double **matrix, int rows, double *y, double *x, int *iterations, double error);
#endif // JACOBIH
