#ifndef POTENCIAINVERSAH
#define POTENCIAINVERSAH
void free_solution_eigen_(double **solution);
double **eigen_menor(double **matrix, int m, double **eigen_old, int k, int subespacio);
double **eigen_menores(double **matrix,int m, int n, int *number, double *eigen_valores, int m_eigen, int subespacio, double**);
#endif /*POTENCIAINVERSAH*/
