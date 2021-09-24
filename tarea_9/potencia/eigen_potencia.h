#ifndef POTENCIA_
#define POTENCIA_
void free_solution_eigen(double **solution);
void normalizar_vector(double *vector, int m);
double dot_vector(double *a, double *b, int m);
double *dot(double **a, double *b, int m, int n);
double **eigen_dominante(char *name, int *m_c);
#endif /*PTENCIA_*/
