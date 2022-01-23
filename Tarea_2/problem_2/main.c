//Giovanny Encinia
//17/08/2021
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ONE 1
#define SQUARE(x) (pow(x, 2))
#define SIZE(x) (sizeof(x)/sizeof(x[0]))

double function(double x)
{
    /*Calculate the function 1/(sqrt(x^2 -1)) -xevaluated in x
    and return the result*/
    double result;
    result = ONE / (sqrt(SQUARE(x) - ONE) - x);

    return  result;
}

double function_op(double x)
{
    /*Calculate the function x-sqrt(x^2 - 1)evaluated in x
    and return the result*/
    double result;
    result = -(x + sqrt(SQUARE(x) - ONE));

    return result;
}

int main()
{
    int i = 0;
    double x[10] = {
                    10000, 15000, 54000, 90000,
                    95000, 100000, 150000, 200000,
                    1000000, 50505000
                  };

    while(i < SIZE(x))
    {
        printf("Value of x= %f\n", x[i]);
        printf("normal function value:%f\n", function(x[i]));
        printf("transformated funcion value: %f\n\n", function_op(x[i]));
        i++;
    }

    return 0;
}
