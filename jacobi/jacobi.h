#ifndef JACOBIH
#define JACOBIH
void solve_jacobi(char *name_mat, char *name_vec);
int convergencia(double **matrix, int rows, double *x, double *y);
void jacobi(double **matrix, int rows, double *y, double *x, int *iterations);
#endif // JACOBIH
