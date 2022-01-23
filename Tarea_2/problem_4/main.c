#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define F(x) sin(x)
#define N 10
#define ZERO 0
#define ONE 1
#define PI_2 1.57079632679

#define A ZERO
#define B PI_2
#define DX() ((B-A)/N)

double riemann(int n, int i)
{
    /*This is a general function that calculates the
    riemann''s sum,  it can be Lr or Rn depending of
    the i and the n*/

    double sum = ZERO;
    double x_i;

    x_i = A + i * DX();//initialize the first x_i

    while(i <= n)
    {
        sum += F(x_i);
        x_i += DX();
        i++;

    }

    return  sum * DX();
}

int main()
{
    double rn, ln;

    rn = riemann(N, ONE);//begin with i=1 until n
    ln = riemann(N - ONE, ZERO);//begin with i=0 until n-1
    printf("  R_n = %lf, Er = %.9lf\n", rn, fabs(ONE - rn));
    printf("  L_n = %lf, Er = %.9lf\n", ln, fabs(ONE - ln));

    return 0;
}
