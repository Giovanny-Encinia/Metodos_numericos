//Giovanny Encinia
// 08/18/2021
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 25// terms number of the mclaurin's serie
#define ONE 1
#define  ZERO 0
#define E_R(e_x, result) (fabs(e_x - result)/fabs(e_x))
#define DELTA 0.00001
#define X 10.5 // value x to evaluate

long factorial(long k, long *memo)
{
    /*This function calculates the factorial with memoization*/
    long result;

    if(memo[k])
    {
        result =  memo[k]; // search in the array memo
    }
    else
    {
        result = k*factorial(k-ONE, memo);
    }

    memo[k] = result; // save the new result in memo

    return result;
}

long double power(long double x, int k, long double *memo_pow)
{
    /*Calculate power of x with memoization*/
    long double result;

    if(memo_pow[k])
    {
        result = memo_pow[k];//search
    }
    else
    {
        result = power(x, k -ONE, memo_pow) * x;// kernel recursion
    }

    memo_pow[k] = result;// save in memo

    return result;
}

double e_mclaurin(long double x, int n, long *memo, \
                  long double *memo_pow, long double *memo_taylor)
{
    /*mclaurine^x serie with memoization*/
    long double sum;

    if(memo_taylor[n])
    {
        sum = memo_taylor[n];
    }
    else
    {
        sum = e_mclaurin(x, n - ONE, memo, memo_pow, memo_taylor) \
        + power(x, n, memo_pow) / factorial(n, memo);
    }

    memo_taylor[n] = sum;

    return sum;
}

int main()
{
    long *memo\
     = (long*)calloc(SIZE, sizeof(long));//factorial
    long double *memo_pow\
     = (long double *)calloc(SIZE, sizeof(long double));//power
    long double *memo_taylor\
     = (long double *)calloc(SIZE, sizeof(long double));//term serie

    int i = ZERO;
    long double x;
    long double result = ZERO;
    long double e_x;
    //x = X;
    //e_x = exp(X);
    printf("Give me a value of x\n");
    scanf("%Lf", &x);
    e_x = exp(x);

    if(memo == NULL || memo_pow == NULL || memo_taylor == NULL)
    {
        printf("Memory not asigned, full memory\n");
    }
    else
    {
    memo[ZERO] = memo[ONE] = ONE;// 0! = 1, 1! = 1
    memo_pow[ZERO] = ONE; // x^0 = 1
    memo_taylor[ZERO] = ONE;

    //check the relative error or the terms number
    while(i < SIZE)
    {
        result = e_mclaurin(x, i, memo, memo_pow, memo_taylor);
        i++;
        if(E_R(e_x, result) <= DELTA) // check relative error
        {
            break;
        }
    }

    if(E_R(e_x, result) > DELTA) //check solution
    {
        printf("solution not found\n");
        printf("relative error big with n <= %d\n", i);
    }
    else
    {
        printf("solution found with Er=%lf\n", E_R(e_x, result));
        printf("n = %d, f(%Lf) = %.9Lf\n", i, x, result);
    }

    }

    free(memo);
    free(memo_pow);
    free(memo_taylor);

    return ZERO;
}
