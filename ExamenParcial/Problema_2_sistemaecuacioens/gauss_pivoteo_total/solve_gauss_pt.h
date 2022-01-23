#ifndef GAUSST
#define GAUSST


double sumatoria_(double **matrix,  double *x, int i, \
  int n, int, int);
void solve_triangular_super_(double **matrix, int rows, double *x);
double maximo(double **matrix, int m, int i_o, int *i_c, int *j_c);
int pivoteo(double **matrix, int m, int *signo, double *cambios_x);
int gauss(double **matrix, int m, double *x, double *y, int *signo);

#endif /* GAUST*/
