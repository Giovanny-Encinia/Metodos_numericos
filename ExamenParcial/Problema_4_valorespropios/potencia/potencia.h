#ifndef POTENCIA_H
double **eigen_mayores(double **matrix, int m, int n, int *number, double *eigen_valores, int m_eigen, int subespacio, double **eigenvectores);
double **eigen_mayor(double **matrix, int m, double **eigen_old , int k, int subespacio);
void free_solution_eigen(double **solution);
#endif // POTENCIA_H
