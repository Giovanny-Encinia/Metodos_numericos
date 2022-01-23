#ifndef CHOLESKY_
#define CHOLESKY_
double sum_cholesky(double **cholesky_mat, int m, int i, int j);
void cholesky_value(double **cholesky_mat, int m, int i, int j, double (*f)(int, int));
double **create_space_cholesky(int rows);
void cholesky(double **matrix, int rows, double (*f)(int, int));
#endif // CHOLESKY_
