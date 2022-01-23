#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
//constants
#define ZERO 0
#define ONE 1
#define TWO 2
#define EPSILON 0.000001
#define LIMIT 100000
//Macros
#define MAX(a, b) ((a)<(b)?(b):(a))
#define CRITERIA(a, b) (fabs((b) - (a)) / MAX(1, (b)))

//Declare functions(), to solve the homework
float F_x(float x)
{
    return (exp(x) + pow(TWO, (-(x))) + 2*cos(x) - 6);
}

float F_p_x(float x)
{
    return (exp(x) - log(2) / pow(TWO, x) - 2*sin(x));
}

float G_x(float x)
{
    return (log((x) - 1) + cos((x)-1));
}

float G_p_x(float x)
{
    return (1 / (x - 1) - sin(x - 1));
}

float H_x(float x)
{
    return (230*pow(x, 4) + 18*pow(x, 3)+9*pow(x, 2)-221*x-9);
}

float H_p_x(float x)
{
    return (920*pow(x, 3)+54*pow(x, 2)+18*x-221);
}


void print_iter(int i, float time)
{
    /*Print the execution time of the method and the number of iterations*/

    if(i < LIMIT)
    {
        printf("\t\tThe root was founded in %d iterations\n", i);
        printf("\t\tThe total time for that was %lf seconds\n\n", time);
    }
    else
    {
        printf("Exact root do not founded u.u\n");
    }

}

float newton(float x_0, float (*function)(float), float (*f_p)(float))
{
    float x = x_0, x_before = x + ONE;
    int i = ZERO;
    double elapsed;
    clock_t end, start = clock();

    //three criteria, error relative,  function value, and #iterations
    while(CRITERIA(x_before, x_0) > EPSILON
           && fabs(function(x_0))>EPSILON
          && i < LIMIT)
    {
        if(f_p(x) == ZERO)
            break;

        x_before = x_0;
        x_0  -= function(x_0)/f_p   (x_0); //definition Newton's method
        i++;
    }

    end = clock();
    elapsed = (double)(end - start)/CLOCKS_PER_SEC;
    print_iter(i, elapsed);

    return x_0;
}

float secant(float a, float b, float (*function)(float))
{
    float x_before, f_a, f_b;
    int i = 0;
    double elapsed;
    clock_t end, start = clock();

    while(CRITERIA(b, a)>EPSILON
          && fabs(function(b))>EPSILON
          && i < LIMIT)
    {
        f_a = function(a);
        f_b = function(b);
        x_before = b; //short the interval
        b  = (a*f_b - b*f_a)/(f_b - f_a);// secant method definition
        a = x_before;// new a
        i++;
    }

    end = clock();
    elapsed = (double)(end - start)/CLOCKS_PER_SEC;
    print_iter(i, elapsed);

    return b;
}

float bisection(float a, float b, float (*function)(float))
{
    float x_1;
    int i = ZERO;
    double elapsed;
    clock_t end, start = clock();

    x_1 = a + (b-a) / TWO; //intermediate point

    while(CRITERIA(a, b) > EPSILON && i < LIMIT)
    {


        if( function(a)*function(x_1) < ZERO)//Bolzano theorem
        {
            b = x_1;
        }
        else
        {
            a = x_1;
        }

        x_1 = a + (b - a) /TWO;
        i++;
    }

    end = clock();
    elapsed = (double)(end - start)/CLOCKS_PER_SEC;
    print_iter(i, elapsed);

    return x_1;
}

