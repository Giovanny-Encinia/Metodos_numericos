#ifndef CALORH
#define CALORH
void solve_calor_inferior(double **matrix, double *y, int rows, double *w);
void solve_calor_diagonal(double **matrix, double *w, int rows, double *z);
void solve_calor_superior(double **matrix, double *z, int rows, double *x);
double *generar_y(double Q, double K, double d_i, double d_n, int n, double L);
double **crear_matriz_calor(int rows);
void solve_cholesky_calor(double **matrix, int rows, double *y, double *x);
double *solve_calor_diferencias_finitas(double Q, double K, double d_i, double d_n, int n, double L);
#endif /*CALORH*/
