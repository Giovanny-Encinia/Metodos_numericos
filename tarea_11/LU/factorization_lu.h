#ifndef SOLVELU_
#define SOLVELU_
double sumatoria_triangulares(double **matrix,  double *x, int i, \
  int n, int begin, int end);
double sumatoria_f(double **matrix, int m, int i, int j);
void triangular_super_lu(double **matrix, int rows, double *x, double *y);
void triangular_infer_lu(double **matrix, int rows, double *x, double *y);
int factorization_lu(double **matrix, int m, double *x, double **y);
int solve_lu(double **matrix, int m, double *x, double *y, int factorizada);
#endif /*SOLVELU_*/
