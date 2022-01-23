#ifndef GAUSSSEIDELH
#define GAUSSSEIDELH
int convergencia_gs(double **matrix, int rows, double *x, double *y, double intervalo);
void gauss_seidel(double **matrix, int rows, double *y, double *x, int *iterations, double error);
void *solve_gauss_seidel(char *name_mat, char *name_vec, double error);
#endif /* GAUSSSEIDELH*/
