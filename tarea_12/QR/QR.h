#ifndef QRH
#define QRH
double *qr_eigen(double **matrix, int m);
int condicion_paro(double **q, int m);
void qr_factor(double **matrix, double **r, int m);
#endif